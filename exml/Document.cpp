/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <exml/Document.h>
#include <exml/debug.h>
#include <etk/os/FSNode.h>

#undef __class__
#define __class__	"Document"

exml::Document::Document(void) : 
	m_charset(unicode::EDN_CHARSET_UTF8),
	m_caseSensitive(false),
	m_writeErrorWhenDetexted(true),
	m_comment(""),
	m_Line(""),
	m_filePos(0,0)
{
	
}


bool exml::Document::IGenerate(etk::UString& _data, int32_t _indent) const
{
	for (int32_t iii=0; iii<m_listSub.Size(); iii++) {
		if (NULL!=m_listSub[iii]) {
			m_listSub[iii]->IGenerate(_data, _indent);
		}
	}
	return true;
}

bool exml::Document::Parse(const etk::UString& _data)
{
	EXML_VERBOSE("Start parsing document (type: string) size=" << _data.Size());
	Clear();
	// came from char ==> force in utf8 ...
	m_charset = unicode::EDN_CHARSET_UTF8;
	exml::filePos filePos(1,0);
	m_pos = filePos;
	int32_t parsePos = 0;
	return SubParse(_data, parsePos, m_caseSensitive, filePos, *this, true);
}

bool exml::Document::Generate(etk::UString& _data)
{
	_data = "";
	return IGenerate(_data,0);
}

bool exml::Document::Load(const etk::UString& _file)
{
	// Start loading the XML : 
	EXML_VERBOSE("open file (xml) \"" << _file << "\"");
	Clear();
	etk::FSNode tmpFile(_file);
	if (false == tmpFile.Exist()) {
		EXML_ERROR("File Does not exist : " << _file);
		return false;
	}
	int64_t fileSize = tmpFile.FileSize();
	if (0==fileSize) {
		EXML_ERROR("This file is empty : " << _file);
		return false;
	}
	if (false == tmpFile.FileOpenRead()) {
		EXML_ERROR("Can not open (r) the file : " << _file);
		return false;
	}
	// allocate data
	char * fileBuffer = new char[fileSize+5];
	if (NULL == fileBuffer) {
		EXML_ERROR("Error Memory allocation size=" << fileSize);
		return false;
	}
	// TODO :  change this ... get the charset from the Declaration element ...
	memset(fileBuffer, 0, (fileSize+5)*sizeof(char));
	// load data from the file :
	tmpFile.FileRead(fileBuffer, 1, fileSize);
	// close the file:
	tmpFile.FileClose();
	
	// convert in UTF8 :
	etk::UString tmpDataUnicode(fileBuffer, unicode::EDN_CHARSET_UTF8);
	// remove temporary buffer:
	delete(fileBuffer);
	// parse the data :
	bool ret = Parse(tmpDataUnicode);
	//Display();
	return ret;
}

bool exml::Document::Store(const etk::UString& _file)
{
	etk::UString createData;
	if (false == Generate(createData)) {
		EXML_ERROR("Error while creating the XML : " << _file);
		return false;
	}
	etk::FSNode tmpFile(_file);
	if (false == tmpFile.FileOpenWrite()) {
		EXML_ERROR("Can not open (w) the file : " << _file);
		return false;
	}
	etk::Char endTable = createData.c_str();
	if (tmpFile.FileWrite(endTable, sizeof(char), endTable.Size()) != endTable.Size()) {
		EXML_ERROR("Error while writing output XML file : " << _file);
		tmpFile.FileClose();
		return false;
	}
	tmpFile.FileClose();
	return true;
}

void exml::Document::Display(void)
{
	etk::UString tmpp;
	IGenerate(tmpp, 0);
	EXML_INFO("Generated XML : \n" << tmpp);
}

etk::UString CreatePosPointer(const etk::UString& _line, int32_t _pos)
{
	etk::UString out;
	int32_t iii;
	for (iii=0; iii<_pos && iii<_line.Size(); iii++) {
		if (_line[iii] == '\t') {
			out += "\t";
		} else {
			out += " ";
		}
	}
	for (; iii<_pos; iii++) {
		out += " ";
	}
	out += "^";
	return out;
}

void exml::Document::DisplayError(void)
{
	if (m_comment.Size()==0) {
		EXML_ERROR("No error detected ???");
		return;
	}
	EXML_ERROR(m_filePos << " " << m_comment << "\n"
	           << m_Line << "\n"
	           << CreatePosPointer(m_Line, m_filePos.GetCol()) );
	#ifdef ENABLE_CRITICAL_WHEN_ERROR
		EXML_CRITICAL("detect error");
	#endif
}

void exml::Document::CreateError(const etk::UString& _data, int32_t _pos, const exml::filePos& _filePos, const etk::UString& _comment)
{
	m_comment = _comment;
	m_Line = _data.ExtractLine(_pos);
	m_filePos = _filePos;
	if (true==m_writeErrorWhenDetexted) {
		DisplayError();
	}
}


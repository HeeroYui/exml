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


exml::Document::Document(void) : 
	m_charset(unicode::EDN_CHARSET_UTF8),
	m_caseSensitive(false)
{
	
}


bool exml::Document::Generate(etk::UString& _data, int32_t _indent) const
{
	for (int32_t iii=0; iii<m_listSub.Size(); iii++) {
		if (NULL!=m_listSub[iii]) {
			m_listSub[iii]->Generate(_data, _indent);
		}
	}
	return true;
}


bool exml::Document::Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos)
{
	EXML_DEBUG("start parse : 'document'");
	// in this case : no main node ...
	SubParse(_data, _pos, _caseSensitive, _filePos, true);
	return true;
}


bool exml::Document::Parse(const etk::UString& _data)
{
	EXML_DEBUG("Start parsing document (type: string) size=" << _data.Size());
	// came from char ==> force in utf8 ...
	m_charset = unicode::EDN_CHARSET_UTF8;
	ivec2 filePos(0,1);
	int32_t parsePos = 0;
	return Parse(_data, parsePos, m_caseSensitive, filePos);
}

bool exml::Document::Generate(etk::UString& _data)
{
	return false;
}

bool exml::Document::Load(const etk::UString& _file)
{
	// Start loading the XML : 
	EXML_DEBUG("open file (xml) \"" << _file << "\"");
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
		EXML_ERROR("Can not open the file : " << _file);
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
	Display();
	if (0==Size()) {
		EXML_CRITICAL("lkjlkj");
	}
	return ret;
}

bool exml::Document::Store(const etk::UString& _file)
{
	return false;
}

void exml::Document::Display(void)
{
	etk::UString tmpp;
	Generate(tmpp, 0);
	EXML_INFO("Generated XML : \n" << tmpp);
}


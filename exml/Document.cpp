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
#define __class__ "Document"

exml::Document::Document(void) :
  m_charset(unicode::charsetUTF8),
  m_caseSensitive(false),
  m_writeErrorWhenDetexted(true),
  m_comment(""),
  m_Line(""),
  m_filePos(0,0) {
	
}


bool exml::Document::iGenerate(std::string& _data, int32_t _indent) const {
	for (size_t iii=0; iii<m_listSub.size(); iii++) {
		if (NULL!=m_listSub[iii]) {
			m_listSub[iii]->iGenerate(_data, _indent);
		}
	}
	return true;
}

bool exml::Document::parse(const std::u32string& _data) {
	return parse(to_u8string(_data));
}
bool exml::Document::parse(const std::string& _data) {
	EXML_VERBOSE("Start parsing document (type: string) size=" << _data.size());
	clear();
	// came from char  == > force in utf8 ...
	m_charset = unicode::charsetUTF8;
	exml::filePos filePos(1,0);
	m_pos = filePos;
	int32_t parsePos = 0;
	return subParse(_data, parsePos, m_caseSensitive, filePos, *this, true);
}

bool exml::Document::generate(std::u32string& _data) {
	std::string data;
	bool ret = generate(data);
	_data = to_u32string(data);
	return ret;
}
bool exml::Document::generate(std::string& _data) {
	_data = "";
	return iGenerate(_data,0);
}

bool exml::Document::load(const std::u32string& _data) {
	return load(to_u8string(_data));
}
bool exml::Document::load(const std::string& _file) {
	// Start loading the XML : 
	EXML_VERBOSE("open file (xml) \"" << _file << "\"");
	clear();
	etk::FSNode tmpFile(_file);
	if (false == tmpFile.exist()) {
		EXML_ERROR("File Does not exist : " << _file);
		return false;
	}
	int64_t fileSize = tmpFile.fileSize();
	if (0 == fileSize) {
		EXML_ERROR("This file is empty : " << _file);
		return false;
	}
	if (false == tmpFile.fileOpenRead()) {
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
	tmpFile.fileRead(fileBuffer, 1, fileSize);
	// close the file:
	tmpFile.fileClose();
	
	// convert in UTF8 :
	std::string tmpDataUnicode(fileBuffer);
	// remove temporary buffer:
	delete(fileBuffer);
	// parse the data :
	bool ret = parse(tmpDataUnicode);
	//Display();
	return ret;
}

bool exml::Document::store(const std::u32string& _data) {
	return store(to_u8string(_data));
}
bool exml::Document::store(const std::string& _file) {
	std::string createData;
	if (false == generate(createData)) {
		EXML_ERROR("Error while creating the XML : " << _file);
		return false;
	}
	etk::FSNode tmpFile(_file);
	if (false == tmpFile.fileOpenWrite()) {
		EXML_ERROR("Can not open (w) the file : " << _file);
		return false;
	}
	if (tmpFile.fileWrite((char*)createData.c_str(), sizeof(char), createData.size()) != (int64_t)createData.size()) {
		EXML_ERROR("Error while writing output XML file : " << _file);
		tmpFile.fileClose();
		return false;
	}
	tmpFile.fileClose();
	return true;
}

void exml::Document::display(void) {
	std::string tmpp;
	iGenerate(tmpp, 0);
	EXML_INFO("Generated XML : \n" << tmpp);
}

std::string createPosPointer(const std::string& _line, int32_t _pos) {
	std::string out;
	size_t iii;
	for (iii=0; (int64_t)iii<_pos && iii<_line.size(); iii++) {
		if (_line[iii] == '\t') {
			out += "\t";
		} else {
			out += " ";
		}
	}
	for (; (int64_t)iii<_pos; iii++) {
		out += " ";
	}
	out += "^";
	return out;
}

void exml::Document::displayError(void) {
	if (m_comment.size() == 0) {
		EXML_ERROR("No error detected ???");
		return;
	}
	EXML_ERROR(m_filePos << " " << m_comment << "\n"
	           << m_Line << "\n"
	           << createPosPointer(m_Line, m_filePos.getCol()) );
	#ifdef ENABLE_CRITICAL_WHEN_ERROR
		EXML_CRITICAL("detect error");
	#endif
}

void exml::Document::createError(const std::string& _data, int32_t _pos, const exml::filePos& _filePos, const std::string& _comment) {
	m_comment = _comment;
	m_Line = extract_line(_data, _pos);
	m_filePos = _filePos;
	if (true == m_writeErrorWhenDetexted) {
		displayError();
	}
}


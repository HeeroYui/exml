/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <exml/internal/Document.hpp>
#include <exml/debug.hpp>
#include <etk/uri/provider/provider.hpp>

ememory::SharedPtr<exml::internal::Document> exml::internal::Document::create() {
	return ememory::SharedPtr<exml::internal::Document>(ETK_NEW(exml::internal::Document));
}

exml::internal::Document::Document() :
  m_caseSensitive(false),
  m_writeErrorWhenDetexted(true),
  m_comment(""),
  m_Line(""),
  m_filePos(0,0) {
	
}


bool exml::internal::Document::iGenerate(etk::String& _data, int32_t _indent) const {
	for (size_t iii=0; iii<m_listSub.size(); iii++) {
		if (m_listSub[iii] != null) {
			m_listSub[iii]->iGenerate(_data, _indent);
		}
	}
	return true;
}

bool exml::internal::Document::parse(const etk::String& _data) {
	EXML_VERBOSE("Start parsing document (type: string) size=" << _data.size());
	clear();
	// came from char  == > force in utf8 ...
	exml::FilePos filePos(1,0);
	m_pos = filePos;
	int32_t parsePos = 0;
	return subParse(_data, parsePos, m_caseSensitive, filePos, *this, true);
}

bool exml::internal::Document::generate(etk::String& _data) {
	_data = "";
	return iGenerate(_data,0);
}

bool exml::internal::Document::load(const etk::Uri& _uri) {
	// Start loading the XML : 
	EXML_VERBOSE("open file (xml) " << _uri);
	clear();
	auto fileIo = etk::uri::get(_uri);
	if (fileIo == null) {
		EXML_ERROR("File Does not exist : " << _uri);
		return false;
	}
	if (fileIo->open(etk::io::OpenMode::Read) == false) {
		EXML_ERROR("Can not open (r) the file : " << _uri);
		return false;
	}
	// load data from the file:
	etk::String tmpDataUnicode = fileIo->readAllString();
	// close the file:
	fileIo->close();
	// parse the data:
	bool ret = parse(tmpDataUnicode);
	//Display();
	return ret;
}

bool exml::internal::Document::store(const etk::Uri& _uri) {
	etk::String createData;
	if (generate(createData) == false) {
		EXML_ERROR("Error while creating the XML: " << _uri);
		return false;
	}
	auto fileIo = etk::uri::get(_uri);
	if (fileIo == null) {
		EXML_ERROR("Can not create the uri: " << _uri);
		return false;
	}
	if (fileIo->open(etk::io::OpenMode::Write) == false) {
		EXML_ERROR("Can not open (r) the file : " << _uri);
		return false;
	}
	fileIo->writeAll(createData);
	fileIo->close();
	return true;
}

void exml::internal::Document::display() {
	etk::String tmpp;
	iGenerate(tmpp, 0);
	EXML_INFO("Generated XML : \n" << tmpp);
}

etk::String createPosPointer(const etk::String& _line, int32_t _pos) {
	etk::String out;
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

void exml::internal::Document::setDisplayError(bool _value) {
	m_writeErrorWhenDetexted = _value;
}

bool exml::internal::Document::getDisplayError() {
	return m_writeErrorWhenDetexted;
}

void exml::internal::Document::displayError() {
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

void exml::internal::Document::createError(const etk::String& _data, int32_t _pos, const exml::FilePos& _filePos, const etk::String& _comment) {
	m_comment = _comment;
	m_Line = etk::extract_line(_data, _pos);
	m_filePos = _filePos;
	if (m_writeErrorWhenDetexted== true) {
		displayError();
	}
}


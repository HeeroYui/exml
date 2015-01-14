/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <exml/Text.h>
#include <exml/debug.h>
#include <exml/Document.h>
#include <regex>

#undef __class__
#define __class__ "Text"


// transform the Text with :
//     "&lt;"   == "<"
//     "&gt;"   == ">"
//     "&amp;"  == "&"
//     "&apos;" == "'"
//     "&quot;" == """
static std::string replaceSpecialChar(const std::string& _inval) {
	std::string out;
	static std::regex regexLT("&lt;");
	static std::regex regexGT("&gt;");
	static std::regex regexAPOS("&apos;");
	static std::regex regexQUOT("&quot;");
	static std::regex regexAMP("&amp;");
	
	out = std::regex_replace(_inval, regexLT, std::string("<"));
	out = std::regex_replace(out, regexGT, std::string(">"));
	out = std::regex_replace(out, regexAPOS, std::string("'"));
	out = std::regex_replace(out, regexQUOT, std::string("\""));
	out = std::regex_replace(out, regexAMP, std::string("&"));
	//EXML_ERROR("INNN '"<< _inval << "' => '" << out << "'");
	return out;
}
static std::string replaceSpecialCharOut(const std::string& _inval) {
	std::string out;
	static std::regex regexLT("<");
	static std::regex regexGT(">;");
	static std::regex regexAMP("&");
	static std::regex regexAPOS("'");
	static std::regex regexQUOT("\"");
	
	out = std::regex_replace(_inval, regexAMP, std::string("&amp;"));
	out = std::regex_replace(out, regexQUOT, std::string("&quot;"));
	out = std::regex_replace(out, regexAPOS, std::string("&apos;"));
	out = std::regex_replace(out, regexGT, std::string("&gt;"));
	out = std::regex_replace(out, regexLT, std::string("&lt;"));
	//EXML_ERROR("OUTTT '"<< _inval << "' => '" << out << "'");
	return out;
}

static bool isWhiteChar(char32_t _val) {
	if(    _val == ' '
	    || _val == '\t'
	    || _val == '\n'
	    || _val == '\r') {
		return true;
	}
	return false;
}

std::shared_ptr<exml::Text> exml::Text::create() {
	return std::shared_ptr<exml::Text>(new exml::Text());
}

std::shared_ptr<exml::Text> exml::Text::create(const std::string& _data) {
	return std::shared_ptr<exml::Text>(new exml::Text(_data));
}

bool exml::Text::iGenerate(std::string& _data, int32_t _indent) const {
	_data += replaceSpecialCharOut(m_value);
	return true;
}

int32_t exml::Text::countLines() const {
	int32_t count = 1;
	for (size_t iii=0; iii<m_value.size(); iii++) {
		if(m_value[iii] == '\n') {
			count++;
		}
	}
	return count;
}

bool exml::Text::iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc) {
	EXML_VERBOSE("start parse : 'text'");
	m_pos = _filePos;
	// search end of the comment :
	for (size_t iii=_pos; iii<_data.size(); iii++) {
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			drawElementParsed(_data[iii], _filePos);
		#endif
		if (_filePos.check(_data[iii]) == true) {
			continue;
		}
		if(    _data[iii] == '>'
		    || _data[iii] == '<') {
			// search whitespace :
			size_t newEnd=iii;
			for (int64_t jjj=(int64_t)iii-1; jjj>(int64_t)_pos; --jjj) {
				if(isWhiteChar(_data[jjj]) == true) {
					newEnd = jjj;
				} else {
					break;
				}
			}
			// find end of value:
			m_value = std::string(_data, _pos, newEnd-(_pos));
			EXML_VERBOSE(" find text '" << m_value << "'");
			_pos = iii-1;
			m_value = replaceSpecialChar(m_value);
			return true;
		}
	}
	CREATE_ERROR(_doc, _data, _pos, _filePos, "Text got end of file without finding end node");
	_pos = _data.size();
	return false;
}


std::shared_ptr<exml::TextCDATA> exml::TextCDATA::create() {
	return std::shared_ptr<exml::TextCDATA>(new exml::TextCDATA());
}

bool exml::TextCDATA::iGenerate(std::string& _data, int32_t _indent) const {
	_data += "<![CDATA[" + m_value +"]]>";
	return true;
}

bool exml::TextCDATA::iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc) {
	EXML_VERBOSE("start parse : 'text::CDATA'");
	m_pos = _filePos;
	// search end of the comment :
	for (size_t iii=_pos; iii+2<_data.size(); iii++) {
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			drawElementParsed(_data[iii], _filePos);
		#endif
		if (_filePos.check(_data[iii]) == true) {
			continue;
		}
		if(    _data[iii] == ']'
		    && _data[iii+1] == ']'
		    && _data[iii+2] == '>') {
			// find end of value:
			_filePos += 2;
			m_value = std::string(_data, _pos, iii-(_pos));
			EXML_VERBOSE(" find text CDATA '" << m_value << "'");
			_pos = iii+2;
			return true;
		}
	}
	CREATE_ERROR(_doc, _data, _pos, _filePos, "text CDATA got end of file without finding end node");
	_pos = _data.size();
	return false;
}


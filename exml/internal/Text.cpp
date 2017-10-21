/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <exml/internal/Text.hpp>
#include <exml/debug.hpp>
#include <exml/internal/Document.hpp>

// transform the Text with :
//     "&lt;"   == "<"
//     "&gt;"   == ">"
//     "&amp;"  == "&"
//     "&apos;" == "'"
//     "&quot;" == """
static etk::String replaceSpecialChar(const etk::String& _inval) {
	etk::String out = _inval;
	out.replace("&lt;", "<");
	out.replace("&gt;", ">");
	out.replace("&apos;", "'");
	out.replace("&quot;", "\"");
	out.replace("&amp;", "&");
	//EXML_ERROR("INNN '"<< _inval << "' => '" << out << "'");
	return out;
}
static etk::String replaceSpecialCharOut(const etk::String& _inval) {
	etk::String out = _inval;
	out.replace("<", "&lt;");
	out.replace(">", "&gt;");
	out.replace("'", "&apos;");
	out.replace("\"", "&quot;");
	out.replace("&", "&amp;");
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

ememory::SharedPtr<exml::internal::Text> exml::internal::Text::create(const etk::String& _data) {
	return ememory::SharedPtr<exml::internal::Text>(ETK_NEW(exml::internal::Text, _data));
}

bool exml::internal::Text::iGenerate(etk::String& _data, int32_t _indent) const {
	_data += replaceSpecialCharOut(m_value);
	return true;
}

int32_t exml::internal::Text::countLines() const {
	int32_t count = 1;
	for (size_t iii=0; iii<m_value.size(); iii++) {
		if(m_value[iii] == '\n') {
			count++;
		}
	}
	return count;
}

bool exml::internal::Text::iParse(const etk::String& _data,
                                  int32_t& _pos,
                                  bool _caseSensitive,
                                  exml::FilePos& _filePos,
                                  exml::internal::Document& _doc) {
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
			m_value = etk::String(_data, _pos, newEnd-(_pos));
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


ememory::SharedPtr<exml::internal::TextCDATA> exml::internal::TextCDATA::create() {
	return ememory::SharedPtr<exml::internal::TextCDATA>(ETK_NEW(exml::internal::TextCDATA));
}

bool exml::internal::TextCDATA::iGenerate(etk::String& _data, int32_t _indent) const {
	_data += "<![CDATA[" + m_value +"]]>";
	return true;
}

bool exml::internal::TextCDATA::iParse(const etk::String& _data,
                                       int32_t& _pos,
                                       bool _caseSensitive,
                                       exml::FilePos& _filePos,
                                       exml::internal::Document& _doc) {
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
			m_value = etk::String(_data, _pos, iii-(_pos));
			EXML_VERBOSE(" find text CDATA '" << m_value << "'");
			_pos = iii+2;
			return true;
		}
	}
	CREATE_ERROR(_doc, _data, _pos, _filePos, "text CDATA got end of file without finding end node");
	_pos = _data.size();
	return false;
}


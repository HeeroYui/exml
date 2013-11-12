/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <exml/Text.h>
#include <exml/debug.h>
#include <exml/Document.h>

#undef __class__
#define __class__ "Text"

bool exml::Text::iGenerate(std::string& _data, int32_t _indent) const {
	_data += m_value;
	return true;
}

int32_t exml::Text::countLines(void) const {
	int32_t count = 1;
	for (int32_t iii=0; iii<m_value.size(); iii++) {
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
	for (int32_t iii=_pos; iii<_data.size(); iii++) {
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			drawElementParsed(_data[iii], _filePos);
		#endif
		if (_filePos.check(_data[iii]) == true) {
			continue;
		}
		if(    _data[iii] == '>'
		    || _data[iii] == '<') {
			// search whitespace :
			int32_t newEnd=iii;
			for( int32_t jjj=iii-1; jjj>_pos; jjj--) {
				if(true == etk::isWhiteChar(_data[jjj])) {
					newEnd = jjj;
				} else {
					break;
				}
			}
			// find end of value:
			m_value = std::string(_data, _pos, newEnd);
			EXML_VERBOSE(" find text '" << m_value << "'");
			_pos = iii-1;
			return true;
		}
	}
	CREATE_ERROR(_doc, _data, _pos, _filePos, "Text got end of file without finding end node");
	_pos = _data.size();
	return false;
}

bool exml::TextCDATA::iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc) {
	EXML_VERBOSE("start parse : 'text::CDATA'");
	m_pos = _filePos;
	// search end of the comment :
	for (int32_t iii=_pos; iii+2<_data.size(); iii++) {
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
			m_value = std::string(_data, _pos, iii);
			EXML_VERBOSE(" find text CDATA '" << m_value << "'");
			_pos = iii+2;
			return true;
		}
	}
	CREATE_ERROR(_doc, _data, _pos, _filePos, "text CDATA got end of file without finding end node");
	_pos = _data.size();
	return false;
}


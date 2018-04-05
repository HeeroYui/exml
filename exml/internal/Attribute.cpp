/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <exml/internal/Attribute.hpp>
#include <exml/debug.hpp>
#include <exml/internal/Document.hpp>

ememory::SharedPtr<exml::internal::Attribute> exml::internal::Attribute::create(const etk::String& _name, const etk::String& _value) {
	return ememory::SharedPtr<exml::internal::Attribute>(ETK_NEW(exml::internal::Attribute, _name, _value));
}

exml::internal::Attribute::Attribute(const etk::String& _name, const etk::String& _value) :
  exml::internal::Node(_value),
  m_name(_name) {
	
}

bool exml::internal::Attribute::iParse(const etk::String& _data, int32_t& _pos, bool _caseSensitive, exml::FilePos& _filePos, exml::internal::Document& _doc) {
	EXML_VERBOSE("start parse : 'attribute'");
	m_pos = _filePos;
	// search end of the comment :
	size_t lastElementName = _pos;
	for (size_t iii=_pos; iii<_data.size(); iii++) {
		_filePos.check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
		 drawElementParsed(_data[iii], _filePos);
		#endif
		if (checkAvaillable(_data[iii], false) == true) {
			lastElementName = iii;
		} else {
			break;
		}
	}
	m_name = etk::String(_data, _pos, lastElementName+1-(_pos));
	if (_caseSensitive == true) {
		m_name = etk::toLower(m_name);
	}
	// count white space :
	exml::FilePos tmpPos;
	int32_t white = countWhiteChar(_data, lastElementName+1, tmpPos);
	_filePos += tmpPos;
	if (lastElementName+white+1 >= _data.size()) {
		CREATE_ERROR(_doc, _data, lastElementName+white+1, _filePos, " parse an xml end with an attribute parsing...");
		return false;
	}
	if (_data[lastElementName+white+1] != '=') {
		CREATE_ERROR(_doc, _data, lastElementName+white+1, _filePos, " error attribute parsing  == > missing '=' ...");
		return false;
	}
	white += countWhiteChar(_data, lastElementName+white+2, tmpPos);
	_filePos += tmpPos;
	
	if (lastElementName+white+2>=_data.size()) {
		CREATE_ERROR(_doc, _data, lastElementName+white+2, _filePos, " parse an xml end with an attribute parsing...");
		return false;
	}
	bool simpleQuoteCase = false;
	if (_data[lastElementName+white+2] == '\'') { // '
		simpleQuoteCase = true;
	}
	if (    _data[lastElementName+white+2] != '"'
	     && _data[lastElementName+white+2] != '\'') { // '
		// parse with no element "  == > direct value separate with space ...
		++_filePos;
		size_t lastAttributePos = lastElementName+white+2;
		for (size_t iii=lastElementName+white+2; iii<_data.size(); iii++) {
			#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
				drawElementParsed(_data[iii], _filePos);
			#endif
			if (_filePos.check(_data[iii]) == true) {
				CREATE_ERROR(_doc, _data, iii, _filePos, "unexpected '\\n' in an attribute parsing");
				return false;
			}
			if(    _data[iii] != ' '
			    && _data[iii] != '/'
			    && _data[iii] != '?'
			    && _data[iii] != '>') {
				lastAttributePos = iii+1;
			} else {
				break;
			}
		}
		m_value = etk::String(_data, lastElementName+white+2, lastAttributePos-(lastElementName+white+2));
		
		EXML_PARSE_ATTRIBUTE(m_pos << " attribute : " << m_name << "=\"" << m_value << "\"");
		
		_pos = lastAttributePos-1;
		return true;
	}
	size_t lastAttributePos = lastElementName+white+3;
	for (size_t iii=lastElementName+white+3; iii<_data.size(); iii++) {
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			drawElementParsed(_data[iii], _filePos);
		#endif
		_filePos.check(_data[iii]);
		if (    (_data[iii] != '"' && simpleQuoteCase == false)
		     || (_data[iii] != '\'' && simpleQuoteCase == true) ) { // '
			lastAttributePos = iii+1;
		} else {
			break;
		}
	}
	m_value = etk::String(_data, lastElementName+white+3, lastAttributePos-(lastElementName+white+3));
	
	EXML_PARSE_ATTRIBUTE(m_pos << " attribute : " << m_name << "=\"" << m_value << "\"");
	
	_pos = lastAttributePos;
	return true;
}

bool exml::internal::Attribute::iGenerate(etk::String& _data, int32_t _indent) const {
	_data += " ";
	_data += m_name;
	_data += "=\"";
	_data += m_value;
	_data += "\"";
	return true;
}

void exml::internal::Attribute::clear() {
	m_name = "";
}


/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <exml/Attribute.h>
#include <exml/debug.h>
#include <exml/Document.h>

#undef __class__
#define __class__	"Attribute"

exml::Attribute::Attribute(const etk::UString& _name, const etk::UString& _value) :
	exml::Node(_value),
	m_name(_name)
{
	
}

bool exml::Attribute::iParse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc)
{
	EXML_VERBOSE("start parse : 'attribute'");
	m_pos = _filePos;
	// search end of the comment :
	int32_t lastElementName = _pos;
	for (int32_t iii=_pos; iii<_data.size(); iii++) {
		_filePos.check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
		 drawElementParsed(_data[iii], _filePos);
		#endif
		if (true == checkAvaillable(_data[iii], false) ) {
			lastElementName = iii;
		} else {
			break;
		}
	}
	m_name = _data.extract(_pos, lastElementName+1);
	if (true == _caseSensitive) {
		m_name.lower();
	}
	// count white space :
	exml::filePos tmpPos;
	int32_t white = countWhiteChar(_data, lastElementName+1, tmpPos);
	_filePos += tmpPos;
	if (lastElementName+white+1>=_data.size()) {
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
	if (_data[lastElementName+white+2] != '"') {
		// parse with no element "  == > direct value separate with space ...
		++_filePos;
		int32_t lastAttributePos = lastElementName+white+2;
		for (int32_t iii=lastElementName+white+2; iii<_data.size(); iii++) {
			#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
				drawElementParsed(_data[iii], _filePos);
			#endif
			if (_filePos.check(_data[iii]) == true) {
				CREATE_ERROR(_doc, _data, iii, _filePos, "unexpected '\\n' in an attribute parsing");
				return false;
			}
			if(    _data[iii]!=' '
			    && _data[iii]!='/'
			    && _data[iii]!='?'
			    && _data[iii]!='>') {
				lastAttributePos = iii+1;
			} else {
				break;
			}
		}
		m_value = _data.extract(lastElementName+white+2, lastAttributePos);
		
		EXML_PARSE_ATTRIBUTE(m_pos << " attribute : " << m_name << "=\"" << m_value << "\"");
		
		_pos = lastAttributePos-1;
		return true;
	}
	int32_t lastAttributePos = lastElementName+white+3;
	for (int32_t iii=lastElementName+white+3; iii<_data.size(); iii++) {
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			drawElementParsed(_data[iii], _filePos);
		#endif
		_filePos.check(_data[iii]);
		if(_data[iii]!='"') {
			lastAttributePos = iii+1;
		} else {
			break;
		}
	}
	m_value = _data.extract(lastElementName+white+3, lastAttributePos);
	
	EXML_PARSE_ATTRIBUTE(m_pos << " attribute : " << m_name << "=\"" << m_value << "\"");
	
	_pos = lastAttributePos;
	return true;
}

bool exml::Attribute::iGenerate(etk::UString& _data, int32_t _indent) const
{
	_data += " ";
	_data += m_name;
	_data += "=\"";
	_data += m_value;
	_data += "\"";
	return true;
}



void exml::Attribute::clear(void)
{
	m_name="";
}


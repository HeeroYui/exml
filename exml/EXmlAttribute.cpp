/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <exml/EXmlAttribute.h>
#include <exml/debug.h>

bool exml::EXmlAttribute::Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos)
{
	EXML_DEBUG("start parse : 'attribute'");
	// search end of the comment :
	int32_t lastElementName = _pos;
	for (int32_t iii=_pos; iii<_data.Size(); iii++) {
		_filePos += ivec2(1,0);
		DrawElementParsed(_data[iii], _filePos);
		if (_data[iii] == '\n') {
			_filePos.setValue(1, _filePos.y()+1);
			EXML_ERROR("unexpected '\\n' in an attribute parsing");
			return false;
		}
		if (true==CheckAvaillable(_data[iii], false) ) {
			lastElementName = iii;
		} else {
			break;
		}
	}
	m_name = _data.Extract(_pos, lastElementName+1);
	
	if (lastElementName+1>=_data.Size()) {
		EXML_ERROR(" parse an xml end with an attribute parsing...");
		return false;
	}
	if (_data[lastElementName+1] != '=') {
		EXML_ERROR(" error attribute parsing ==> missing '=' ...");
		return false;
	}
	if (lastElementName+2>=_data.Size()) {
		EXML_ERROR(" parse an xml end with an attribute parsing...");
		return false;
	}
	if (_data[lastElementName+2] != '"') {
		// parse with no element " ==> direct value separate with space ...
		_filePos += ivec2(2,0);
		int32_t lastAttributePos = lastElementName+3;
		for (int32_t iii=lastElementName+2; iii<_data.Size(); iii++) {
			_filePos += ivec2(1,0);
			DrawElementParsed(_data[iii], _filePos);
			if (_data[iii] == '\n') {
				_filePos.setValue(1, _filePos.y()+1);
				EXML_ERROR("unexpected '\\n' in an attribute parsing");
				return false;
			}
			if (_data[iii]!=' ') {
				lastAttributePos = iii;
			} else {
				break;
			}
		}
		m_value = _data.Extract(lastElementName+2, lastAttributePos+1);
		
		_pos = lastAttributePos+1;
		return true;
	}
	_filePos += ivec2(2,0);
	int32_t lastAttributePos = lastElementName+3;
	for (int32_t iii=lastElementName+3; iii<_data.Size(); iii++) {
		_filePos += ivec2(1,0);
		DrawElementParsed(_data[iii], _filePos);
		if (_data[iii] == '\n') {
			_filePos.setValue(1, _filePos.y()+1);
			EXML_ERROR("unexpected '\\n' in an attribute parsing");
			return false;
		}
		if (_data[iii]!='"') {
			lastAttributePos = iii;
		} else {
			break;
		}
	}
	m_value = _data.Extract(lastElementName+3, lastAttributePos+1);
	
	_pos = lastAttributePos+1;
	return true;
}

bool exml::EXmlAttribute::Generate(etk::UString& _data, int32_t _indent)
{
	_data += " ";
	_data += m_name;
	_data += "=\"";
	_data += m_value;
	_data += "\"";
	return true;
}
/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <exml/Text.h>
#include <exml/debug.h>

#undef __class__
#define __class__	"Text"

bool exml::Text::Generate(etk::UString& _data, int32_t _indent) const
{
	_data += m_value;
	return true;
}

int32_t exml::Text::CountLines(void) const
{
	int32_t count = 1;
	for (int32_t iii=0; iii<m_value.Size(); iii++) {
		if(m_value[iii] == '\n') {
			count++;
		}
	}
	return count;
}

bool exml::Text::Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos)
{
	EXML_VERBOSE("start parse : 'text'");
	m_pos = _filePos;
	// search end of the comment :
	for (int32_t iii=_pos; iii<_data.Size(); iii++) {
		_filePos += ivec2(1,0);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			DrawElementParsed(_data[iii], _filePos);
		#endif
		if (_data[iii] == '\n') {
			_filePos.setValue(0, _filePos.y()+1);
			continue;
		}
		if(    _data[iii] == '>'
		    || _data[iii] == '<') {
			// search whitespace :
			int32_t newEnd=iii;
			for( int32_t jjj=iii-1; jjj>_pos; jjj--) {
				if(true==_data[jjj].IsWhiteChar()) {
					newEnd = jjj;
				} else {
					break;
				}
			}
			// find end of value:
			m_value = _data.Extract(_pos, newEnd);
			EXML_VERBOSE(" find text '" << m_value << "'");
			_pos = iii-1;
			return true;
		}
	}
	_pos = _data.Size();
	EXML_ERROR("Text got end of file without finding end node");
	EXML_ERROR(" Data : " << _data);
	return false;
}

bool exml::TextCDATA::Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos)
{
	EXML_VERBOSE("start parse : 'text::CDATA'");
	m_pos = _filePos;
	// search end of the comment :
	for (int32_t iii=_pos; iii+2<_data.Size(); iii++) {
		_filePos += ivec2(1,0);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			DrawElementParsed(_data[iii], _filePos);
		#endif
		if (_data[iii] == '\n') {
			_filePos.setValue(1, _filePos.y()+1);
			continue;
		}
		if(    _data[iii] == ']'
		    && _data[iii+1] == ']'
		    && _data[iii+2] == '>') {
			// find end of value:
			m_value = _data.Extract(_pos, iii);
			EXML_VERBOSE(" find text CDATA '" << m_value << "'");
			_pos = iii+2;
			return true;
		}
	}
	_pos = _data.Size();
	EXML_ERROR("text CDATA got end of file without finding end node");
	return false;
}


/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <exml/EXmlText.h>
#include <exml/debug.h>

bool exml::EXmlText::Generate(etk::UString& _data, int32_t _indent)
{
	_data += m_value;
	return true;
}

int32_t exml::EXmlText::CountLines(void)
{
	int32_t count = 1;
	for (int32_t iii=0; iii<m_value.Size(); iii++) {
		if(m_value[iii] == '\n') {
			count++;
		}
	}
	return count;
}

bool exml::EXmlText::Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos)
{
	EXML_DEBUG("start parse : 'text'");
	// search end of the comment :
	for (int32_t iii=_pos; iii<_data.Size(); iii++) {
		_filePos += ivec2(1,0);
		DrawElementParsed(_data[iii], _filePos);
		if (_data[iii] == '\n') {
			_filePos.setValue(0, _filePos.y()+1);
			continue;
		}
		if(    _data[iii] == '>'
		    || _data[iii] == '<') {
			// search whitespace :
			int32_t newEnd=iii;
			for( int32_t jjj=iii-1; jjj>_pos; jjj--) {
				if(    _data[jjj] == ' '
				    || _data[jjj] == '\n'
				    || _data[jjj] == '\r'
				    || _data[jjj] == '\t') {
					newEnd = jjj;
				} else {
					break;
				}
			}
			// find end of value:
			m_value = _data.Extract(_pos, newEnd);
			EXML_DEBUG(" find text '" << m_value << "'");
			_pos = iii-1;
			return true;
		}
	}
	_pos = _data.Size();
	EXML_ERROR("Text got end of file without finding end node");
	return false;
}

bool exml::EXmlTextCDATA::Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos)
{
	EXML_DEBUG("start parse : 'text::CDATA'");
	// search end of the comment :
	for (int32_t iii=_pos; iii+2<_data.Size(); iii++) {
		_filePos += ivec2(1,0);
		DrawElementParsed(_data[iii], _filePos);
		if (_data[iii] == '\n') {
			_filePos.setValue(1, _filePos.y()+1);
			continue;
		}
		if(    _data[iii] == ']'
		    && _data[iii+1] == ']'
		    && _data[iii+2] == '>') {
			// find end of value:
			m_value = _data.Extract(_pos, iii-1);
			EXML_DEBUG(" find text CDATA '" << m_value << "'");
			_pos = iii+2;
			return true;
		}
	}
	_pos = _data.Size();
	EXML_ERROR("text CDATA got end of file without finding end node");
	return false;
}


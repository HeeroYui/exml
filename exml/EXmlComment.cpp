/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <exml/EXmlComment.h>
#include <exml/debug.h>

bool exml::EXmlComment::Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos)
{
	EXML_DEBUG("start parse : 'comment'");
	// search end of the comment :
	for (int32_t iii=_pos; iii+2<_data.Size(); iii++) {
		_filePos += ivec2(1,0);
		DrawElementParsed(_data[iii], _filePos);
		if (_data[iii] == '\n') {
			_filePos.setValue(1, _filePos.y()+1);
			continue;
		}
		if(    _data[iii] == '-'
		    && _data[iii+1] == '-'
		    && _data[iii+2] == '>') {
			// find end of value:
			m_value = _data.Extract(_pos, iii-1);
			EXML_DEBUG(" find comment '" << m_value << "'");
			_pos = iii+2;
			return true;
		}
	}
	_pos = _data.Size();
	EXML_ERROR("comment got end of file without finding end node");
	return false;
}

bool exml::EXmlComment::Generate(etk::UString& _data, int32_t _indent) const
{
	AddIndent(_data, _indent);
	_data += "<!--";
	_data += m_value;
	_data += "-->\n";
	return true;
}
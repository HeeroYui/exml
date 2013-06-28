/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <exml/Declaration.h>
#include <exml/debug.h>

#undef __class__
#define __class__	"Declaration"

/* basic declaration have 3 attributes:
	version
	encoding
	standalone
	<?xml version="1.0" encoding="UTF-8" ?>
*/

exml::Declaration::Declaration(const etk::UString& _version, unicode::charset_te _format, bool _standalone)
{
	m_value = "xml";
	if (_version.Size()!=0) {
		SetAttribute("version", _version);
	}
	if (_format!=unicode::EDN_CHARSET_UTF8) {
		SetAttribute("encoding", "UTF-8");
	} else {
		EXML_ERROR("Actually does not supported other charset than UTF8");
		SetAttribute("encoding", "UTF-8");
	}
	if (_standalone==true) {
		SetAttribute("standalone", "true");
	} else {
		SetAttribute("standalone", "true");
	}
}

bool exml::Declaration::Generate(etk::UString& _data, int32_t _indent) const
{
	AddIndent(_data, _indent);
	_data += "<?";
	_data += m_value;
	exml::AttributeList::Generate(_data, _indent);
	_data += "?>\n";
	return true;
}

bool exml::Declaration::Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos)
{
	EXML_VERBOSE("start parse : 'declaration'");
	m_pos = _filePos;
	// search end of the comment :
	for (int32_t iii=_pos; iii+1<_data.Size(); iii++) {
		_filePos += ivec2(1,0);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			DrawElementParsed(_data[iii], _filePos);
		#endif
		if (_data[iii] == '\n') {
			_filePos.setValue(1, _filePos.y()+1);
			continue;
		}
		if(    _data[iii] == '>'
		    || _data[iii] == '<') {
			// an error occured : 
			EXML_ERROR(_filePos << " find '>' or '<'  instead of '?>'");
			return false;
		}
		if(    _data[iii] == '?'
		    && _data[iii+1] == '>') {
			// find end of value:
			m_value = _data.Extract(_pos, iii-1);
			EXML_DEBUG(" find declaration '" << m_value << "'");
			_pos = iii+1;
			return true;
		}
		if (true == CheckAvaillable(_data[iii], true)) {
			// we find an attibute ==> create a new and parse it :
			exml::Attribute* attribute = new exml::Attribute();
			if (NULL==attribute) {
				EXML_ERROR(_filePos << " Allocation error ...");
				return false;
			}
			_pos = iii;
			if (false==attribute->Parse(_data, _pos, _caseSensitive, _filePos)) {
				delete(attribute);
				return false;
			}
			iii = _pos;
			m_listAttribute.PushBack(attribute);
			continue;
		}
	}
	_pos = _data.Size();
	EXML_ERROR("Text got end of file without finding end node");
	return false;
}


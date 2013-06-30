/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <exml/Node.h>
#include <exml/debug.h>

#undef __class__
#define __class__	"Node"


etk::CCout& exml::operator <<(etk::CCout& _os, const exml::filePos& _obj)
{
	_os << "(l=";
	_os << _obj.GetLine();
	_os << ",c=";
	_os << _obj.GetCol();
	_os << ")";
	return _os;
}

exml::Node::Node(const etk::UString& _value) :
	m_pos(0,0),
	m_value(_value)
{
	// nothing to do.
}

void exml::Node::AddIndent(etk::UString& _data, int32_t _indent) const
{
	for (int32_t iii=0; iii<_indent; iii++) {
		_data+="\t";
	}
}

void exml::Node::DrawElementParsed(const etk::UniChar& _val, const exml::filePos& _filePos) const
{
	if (_val=='\n') {
		EXML_DEBUG(_filePos << " Parse '\\n'");
	} else if (_val=='\t') {
		EXML_DEBUG(_filePos << " Parse '\\t'");
	} else {
		EXML_DEBUG(_filePos << " Parse '" << _val << "'");
	}
}

bool exml::Node::CheckAvaillable(const etk::UniChar& _val, bool _firstChar) const
{
	if(    _val == '!'
	    || _val == '"'
	    || _val == '#'
	    || _val == '$'
	    || _val == '%'
	    || _val == '&'
	    || _val == '\'' // '
	    || _val == '('
	    || _val == ')'
	    || _val == '*'
	    || _val == '+'
	    || _val == ','
	    || _val == '/'
	    || _val == ';'
	    || _val == '<'
	    || _val == '='
	    || _val == '>'
	    || _val == '?'
	    || _val == '@'
	    || _val == '['
	    || _val == '\\'
	    || _val == ']'
	    || _val == '^'
	    || _val == '`'
	    || _val == '{'
	    || _val == '|'
	    || _val == '}'
	    || _val == '~'
	    || _val == ' '
	    || _val == '\n'
	    || _val == '\t'
	    || _val == '\r') {
		return false;
	}
	if (true == _firstChar) {
		if(    _val == '-'
		    || _val == '.'
		    || (    _val >= '0'
		         && _val <= '9') ) {
			return false;
		}
	}
	return true;
}


int32_t exml::Node::CountWhiteChar(const etk::UString& _data, int32_t _pos, exml::filePos& _filePos) const
{
	_filePos.Clear();
	int32_t white=0;
	for (int32_t iii=_pos; iii<_data.Size(); iii++) {
		_filePos.Check(_data[iii]);
		if(true == _data[iii].IsWhiteChar()) {
			white++;
		} else {
			break;
		}
	}
	--_filePos;
	return white;
}

void exml::Node::Clear(void)
{
	m_value="";
	m_pos.Clear();
}

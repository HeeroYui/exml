/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <exml/EXmlNode.h>
#include <exml/debug.h>


exml::EXmlNode::EXmlNode(const etk::UString& _value) :
	m_value(_value)
{
	
}

void exml::EXmlNode::AddIndent(etk::UString& _data, int32_t _indent)
{
	for (int32_t iii=0; iii<_indent; iii++) {
		_data+="\t";
	}
}

void exml::EXmlNode::DrawElementParsed(const etk::UniChar& _val, const ivec2& _filePos)
{
	if (_val=='\n') {
		EXML_DEBUG(_filePos << " Parse '\\n'");
	} else if (_val=='\t') {
		EXML_DEBUG(_filePos << " Parse '\\t'");
	} else {
		EXML_DEBUG(_filePos << " Parse '" << _val << "'");
	}
}


// !"#$%&'()*+,/;<=>?@[\]^`{|}~ ou une espace et ne peut pas commencer par -. ou un chiffre.
bool exml::EXmlNode::CheckAvaillable(const etk::UniChar& _val, bool _firstChar)
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

int32_t exml::EXmlNode::CountWhiteChar(const etk::UString& _data, int32_t _pos)
{
	int32_t white=0;
	for (int32_t iii=_pos; iii<_data.Size(); iii++) {
		if(    _data[iii] == ' '
		    || _data[iii] == '\t'
		    || _data[iii] == '\n'
		    || _data[iii] == '\r') {
			white++;
		} else {
			break;
		}
	}
	return white;
}


			bool IsDocument(void) { return GetType()==exml::typeDocument; };
			bool IsAttribute(void) { return GetType()==exml::typeAttribute; };
			bool IsComment(void) { return GetType()==exml::typeComment; };
			bool IsDeclaration(void) { return GetType()==exml::typeDeclaration; };
			bool IsElement(void) { return GetType()==exml::typeElement; };
			bool IsText(void) { return GetType()==exml::typeText; };


exml::EXmlDocument* exml::EXmlNode::ToDocument(void)
{
	if (GetType()==exml::typeDocument) {
		return static_cast<exml::*>(*this);
	}
	return NULL;
}

exml::EXmlAttribute* exml::EXmlNode::ToAttribute(void)
{
	if (GetType()==exml::typeDocument) {
		return static_cast<exml::EXmlAttribute*>(*this);
	}
	return NULL;
}

exml::EXmlComment* exml::EXmlNode::ToComment(void)
{
	if (GetType()==exml::typeDocument) {
		return static_cast<exml::EXmlComment*>(*this);
	}
	return NULL;
}

exml::EXmlDeclaration* exml::EXmlNode::ToDeclaration(void)
{
	if (GetType()==exml::typeDocument) {
		return static_cast<exml::EXmlDeclaration*>(*this);
	}
	return NULL;
}

exml::EXmlElement* exml::EXmlNode::ToElement(void)
{
	if (GetType()==exml::typeDocument) {
		return static_cast<exml::EXmlElement*>(*this);
	}
	return NULL;
}

exml::EXmlText* exml::EXmlNode::ToText(void)
{
	if (GetType()==exml::typeDocument) {
		return static_cast<exml::EXmlText*>(*this);
	}
	return NULL;
}




/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <exml/Node.h>
#include <exml/debug.h>

static bool isWhiteChar(char32_t _val) {
	if(    _val == ' '
	    || _val == '\t'
	    || _val == '\n'
	    || _val == '\r') {
		return true;
	}
	return false;
}

exml::Node::Node(const std::string& _value) :
    m_pos(0,0),
    m_value(_value) {
	// nothing to do.
}


void exml::Node::addIndent(std::string& _data, int32_t _indent) const {
	for (int32_t iii=0; iii<_indent; iii++) {
		_data += "\t";
	}
}

void exml::Node::drawElementParsed(char32_t _val, const exml::FilePos& _filePos) const {
	if (_val == '\n') {
		EXML_DEBUG(_filePos << " parse '\\n'");
	} else if (_val == '\t') {
		EXML_DEBUG(_filePos << " parse '\\t'");
	} else {
		EXML_DEBUG(_filePos << " parse '" << _val << "'");
	}
}

bool exml::Node::checkAvaillable(char32_t _val, bool _firstChar) const {
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
	if (_firstChar == true) {
		if(    _val == '-'
		    || _val == '.'
		    || (    _val >= '0'
		         && _val <= '9') ) {
			return false;
		}
	}
	return true;
}


int32_t exml::Node::countWhiteChar(const std::string& _data, int32_t _pos, exml::FilePos& _filePos) const {
	_filePos.clear();
	int32_t white=0;
	for (size_t iii=_pos; iii<_data.size(); iii++) {
		_filePos.check(_data[iii]);
		if(isWhiteChar(_data[iii]) == true) {
			white++;
		} else {
			break;
		}
	}
	--_filePos;
	return white;
}

bool exml::Node::iGenerate(std::string& _data, int32_t _indent) const {
	return true;
}

const exml::FilePos& exml::Node::getPos() const {
	return m_pos;
}

void exml::Node::clear() {
	m_value = "";
	m_pos.clear();
}

void exml::Node::setValue(std::string _value) {
	m_value = _value;
}

const std::string& exml::Node::getValue() const {
	return m_value;
}

enum exml::nodeType exml::Node::getType() const {
	return nodeType_node;
}

ememory::SharedPtr<exml::Document> exml::Node::toDocument() {
	return nullptr;
}

ememory::SharedPtr<const exml::Document> exml::Node::toDocument() const {
	return nullptr;
}

ememory::SharedPtr<exml::Attribute> exml::Node::toAttribute() {
	return nullptr;
}

ememory::SharedPtr<const exml::Attribute> exml::Node::toAttribute() const {
	return nullptr;
}

ememory::SharedPtr<exml::Comment> exml::Node::toComment() {
	return nullptr;
}

ememory::SharedPtr<const exml::Comment> exml::Node::toComment() const {
	return nullptr;
}

ememory::SharedPtr<exml::Declaration> exml::Node::toDeclaration() {
	return nullptr;
}

ememory::SharedPtr<const exml::Declaration> exml::Node::toDeclaration() const {
	return nullptr;
}

ememory::SharedPtr<exml::Element> exml::Node::toElement() {
	return nullptr;
}

ememory::SharedPtr<const exml::Element> exml::Node::toElement() const {
	return nullptr;
}

ememory::SharedPtr<exml::Text> exml::Node::toText() {
	return nullptr;
}

ememory::SharedPtr<const exml::Text> exml::Node::toText() const{
	return nullptr;
}

bool exml::Node::isDocument() const {
	return getType() == exml::nodeType_document;
}

bool exml::Node::isAttribute() const {
	return getType() == exml::nodeType_attribute;
}

bool exml::Node::isComment() const {
	return getType() == exml::nodeType_comment;
}

bool exml::Node::isDeclaration() const {
	return getType() == exml::nodeType_declaration;
}

bool exml::Node::isElement() const {
	return getType() == exml::nodeType_element;
}

bool exml::Node::isText() const {
	return getType() == exml::nodeType_text;
}


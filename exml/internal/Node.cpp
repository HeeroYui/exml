/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <exml/internal/Node.h>
#include <exml/internal/Document.h>
#include <exml/internal/Attribute.h>
#include <exml/internal/Comment.h>
#include <exml/internal/Declaration.h>
#include <exml/internal/Element.h>
#include <exml/internal/Text.h>
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

exml::internal::Node::Node(const std::string& _value) :
    m_pos(0,0),
    m_value(_value) {
	// nothing to do.
}


void exml::internal::Node::addIndent(std::string& _data, int32_t _indent) const {
	for (int32_t iii=0; iii<_indent; iii++) {
		_data += "\t";
	}
}

void exml::internal::Node::drawElementParsed(char32_t _val, const exml::FilePos& _filePos) const {
	if (_val == '\n') {
		EXML_DEBUG(_filePos << " parse '\\n'");
	} else if (_val == '\t') {
		EXML_DEBUG(_filePos << " parse '\\t'");
	} else {
		EXML_DEBUG(_filePos << " parse '" << _val << "'");
	}
}

bool exml::internal::Node::checkAvaillable(char32_t _val, bool _firstChar) const {
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


int32_t exml::internal::Node::countWhiteChar(const std::string& _data, int32_t _pos, exml::FilePos& _filePos) const {
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

bool exml::internal::Node::iGenerate(std::string& _data, int32_t _indent) const {
	return true;
}

const exml::FilePos& exml::internal::Node::getPos() const {
	return m_pos;
}

void exml::internal::Node::clear() {
	m_value = "";
	m_pos.clear();
}

void exml::internal::Node::setValue(std::string _value) {
	m_value = _value;
}

const std::string& exml::internal::Node::getValue() const {
	return m_value;
}

enum exml::nodeType exml::internal::Node::getType() const {
	return nodeType::node;
}

ememory::SharedPtr<exml::internal::Document> exml::internal::Node::toDocument() {
	return nullptr;
}

const ememory::SharedPtr<exml::internal::Document> exml::internal::Node::toDocument() const {
	return nullptr;
}

ememory::SharedPtr<exml::internal::Attribute> exml::internal::Node::toAttribute() {
	return nullptr;
}

const ememory::SharedPtr<exml::internal::Attribute> exml::internal::Node::toAttribute() const {
	return nullptr;
}

ememory::SharedPtr<exml::internal::Comment> exml::internal::Node::toComment() {
	return nullptr;
}

const ememory::SharedPtr<exml::internal::Comment> exml::internal::Node::toComment() const {
	return nullptr;
}

ememory::SharedPtr<exml::internal::Declaration> exml::internal::Node::toDeclaration() {
	return nullptr;
}

const ememory::SharedPtr<exml::internal::Declaration> exml::internal::Node::toDeclaration() const {
	return nullptr;
}

ememory::SharedPtr<exml::internal::Element> exml::internal::Node::toElement() {
	return nullptr;
}

const ememory::SharedPtr<exml::internal::Element> exml::internal::Node::toElement() const {
	return nullptr;
}

ememory::SharedPtr<exml::internal::Text> exml::internal::Node::toText() {
	return nullptr;
}

const ememory::SharedPtr<exml::internal::Text> exml::internal::Node::toText() const{
	return nullptr;
}

bool exml::internal::Node::isDocument() const {
	return getType() == exml::nodeType::document;
}

bool exml::internal::Node::isAttribute() const {
	return getType() == exml::nodeType::attribute;
}

bool exml::internal::Node::isComment() const {
	return getType() == exml::nodeType::comment;
}

bool exml::internal::Node::isDeclaration() const {
	return getType() == exml::nodeType::declaration;
}

bool exml::internal::Node::isElement() const {
	return getType() == exml::nodeType::element;
}

bool exml::internal::Node::isText() const {
	return getType() == exml::nodeType::text;
}


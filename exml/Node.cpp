/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <exml/Node.h>
#include <exml/internal/Node.h>
#include <exml/debug.h>
#include <exml/Attribute.h>
#include <exml/Comment.h>
#include <exml/Declaration.h>
#include <exml/Document.h>
#include <exml/Element.h>
#include <exml/Text.h>

std::ostream& exml::operator <<(std::ostream& _os, const exml::Node& _obj) {
	_os << "{";
	_os << "Node XML: " << _obj.getType();
	if (_obj.isElement() == true) {
		_os << " <" << _obj.getValue() << ">";
	};
	_os << "}";
	return _os;
}


exml::Node::Node(ememory::SharedPtr<exml::internal::Node> _internalNode) :
  m_data(_internalNode) {
	// nothing to DO ...
}

exml::Node::Node() :
  m_data(nullptr) {
	
}

bool exml::Node::exist() const {
	if (m_data == nullptr) {
		return false;
	}
	return true;
}

exml::FilePos exml::Node::getPos() const {
	if (m_data == nullptr) {
		return exml::FilePos(0,0);
	}
	return m_data->getPos();
}

void exml::Node::setValue(std::string _value) {
	if (m_data == nullptr) {
		EXML_ERROR(" can not set value: '" << _value << "'");
		return;
	}
	m_data->setValue(_value);
}

const std::string& exml::Node::getValue() const {
	if (m_data == nullptr) {
		static std::string errorString = "";
		EXML_ERROR(" can not get value ...");
		return errorString;
	}
	return m_data->getValue();
}

enum exml::nodeType exml::Node::getType() const {
	if (m_data == nullptr) {
		EXML_ERROR("Can not get type ...");
		return exml::nodeType::unknow;
	}
	return m_data->getType();
}

exml::Document exml::Node::toDocument() {
	return exml::Document(m_data);
}

const exml::Document exml::Node::toDocument() const {
	return exml::Document(m_data);
}

exml::Attribute exml::Node::toAttribute() {
	return exml::Attribute(m_data);
}

const exml::Attribute exml::Node::toAttribute() const {
	return exml::Attribute(m_data);
}

exml::Comment exml::Node::toComment() {
	return exml::Comment(m_data);
}

const exml::Comment exml::Node::toComment() const {
	return exml::Comment(m_data);
}

exml::Declaration exml::Node::toDeclaration() {
	return exml::Declaration(m_data);
}

const exml::Declaration exml::Node::toDeclaration() const {
	return exml::Declaration(m_data);
}

exml::Element exml::Node::toElement() {
	return exml::Element(m_data);
}

const exml::Element exml::Node::toElement() const {
	return exml::Element(m_data);
}

exml::Text exml::Node::toText() {
	return exml::Text(m_data);
}

const exml::Text exml::Node::toText() const {
	return exml::Text(m_data);
}

bool exml::Node::isDocument() const {
	if (m_data == nullptr) {
		return false;
	}
	return m_data->isDocument();
}

bool exml::Node::isAttribute() const {
	if (m_data == nullptr) {
		return false;
	}
	return m_data->isAttribute();
}

bool exml::Node::isComment() const {
	if (m_data == nullptr) {
		return false;
	}
	return m_data->isComment();
}

bool exml::Node::isDeclaration() const {
	if (m_data == nullptr) {
		return false;
	}
	return m_data->isDeclaration();
}

bool exml::Node::isElement() const {
	if (m_data == nullptr) {
		return false;
	}
	return m_data->isElement() || m_data->isDocument();
}

bool exml::Node::isText() const {
	if (m_data == nullptr) {
		return false;
	}
	return m_data->isText();
}

void exml::Node::clear() {
	if (m_data == nullptr) {
		return;
	}
	return m_data->clear();
}

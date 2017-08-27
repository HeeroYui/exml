/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <exml/Attribute.hpp>
#include <exml/debug.hpp>
#include <exml/internal/Attribute.hpp>

exml::Attribute::Attribute(ememory::SharedPtr<exml::internal::Node> _internalNode) :
  exml::Node(_internalNode) {
	if (m_data == nullptr) {
		return;
	}
	if (m_data->isAttribute() == false) {
		// try to set wrong type inside ... ==> remove it ...
		m_data = nullptr;
	}
}

exml::Attribute::Attribute(const exml::Attribute& _obj) :
  exml::Node(_obj.m_data) {
	
}
/*
exml::Attribute::Attribute(nullptr) :
  exml::Node(nullptr) {
	
}
*/
exml::Attribute::Attribute(const etk::String& _name, const etk::String& _value) :
  exml::Node() {
	m_data = exml::internal::Attribute::create(_name, _value);
}

exml::Attribute& exml::Attribute::operator= (const exml::Attribute& _obj) {
	m_data = _obj.m_data;
	return *this;
}

void exml::Attribute::setName(const etk::String& _name){
	if (m_data == nullptr) {
		EXML_DEBUG(" can not setName (nullptr) ...");
		return;
	}
	static_cast<exml::internal::Attribute*>(m_data.get())->setName(_name);
}

const etk::String& exml::Attribute::getName() const {
	if (m_data == nullptr) {
		static etk::String errorValue = "";
		EXML_DEBUG(" can not setName (nullptr) ...");
		return errorValue;
	}
	return static_cast<const exml::internal::Attribute*>(m_data.get())->getName();
}

void exml::Attribute::clear() {
	if (m_data == nullptr) {
		EXML_DEBUG(" can not setName (nullptr) ...");
		return;
	}
	static_cast<exml::internal::Attribute*>(m_data.get())->clear();
}

etk::Pair<etk::String, etk::String> exml::Attribute::getPair() const {
	if (m_data == nullptr) {
		EXML_DEBUG(" can not setName (nullptr) ...");
		return etk::Pair<etk::String, etk::String>("","");
	}
	return etk::Pair<etk::String, etk::String>(static_cast<const exml::internal::Attribute*>(m_data.get())->getName(),
	                                           static_cast<const exml::internal::Attribute*>(m_data.get())->getValue());
}

ememory::SharedPtr<exml::internal::Attribute> exml::Attribute::getInternalAttribute() {
	return ememory::staticPointerCast<exml::internal::Attribute>(m_data);
}


/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <exml/Attribute.h>
#include <exml/debug.h>
#include <exml/internal/Attribute.h>

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
exml::Attribute::Attribute(const std::string& _name, const std::string& _value) :
  exml::Node() {
	m_data = exml::internal::Attribute::create(_name, _value);
}

exml::Attribute& exml::Attribute::operator= (const exml::Attribute& _obj) {
	m_data = _obj.m_data;
	return *this;
}

void exml::Attribute::setName(const std::string& _name){
	if (m_data == nullptr) {
		EXML_ERROR(" can not setName (nullptr) ...");
		return;
	}
	static_cast<exml::internal::Attribute*>(m_data.get())->setName(_name);
}

const std::string& exml::Attribute::getName() const {
	if (m_data == nullptr) {
		static std::string errorValue = "";
		EXML_ERROR(" can not setName (nullptr) ...");
		return errorValue;
	}
	return static_cast<const exml::internal::Attribute*>(m_data.get())->getName();
}

void exml::Attribute::clear() {
	if (m_data == nullptr) {
		EXML_ERROR(" can not setName (nullptr) ...");
		return;
	}
	static_cast<exml::internal::Attribute*>(m_data.get())->clear();
}

std::pair<std::string, std::string> exml::Attribute::getPair() const {
	if (m_data == nullptr) {
		EXML_ERROR(" can not setName (nullptr) ...");
		return std::pair<std::string, std::string>("","");
	}
	return std::pair<std::string, std::string>(static_cast<const exml::internal::Attribute*>(m_data.get())->getName(),
	                                           static_cast<const exml::internal::Attribute*>(m_data.get())->getValue());
}

ememory::SharedPtr<exml::internal::Attribute> exml::Attribute::getInternalAttribute() {
	return ememory::staticPointerCast<exml::internal::Attribute>(m_data);
}


/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <exml/Declaration.hpp>
#include <exml/debug.hpp>
#include <exml/internal/Declaration.hpp>

exml::Declaration::Declaration(ememory::SharedPtr<exml::internal::Node> _internalNode) :
  exml::AttributeList(_internalNode) {
	if (m_data == nullptr) {
		return;
	}
	if (m_data->isDeclaration() == false) {
		// try to set wrong type inside ... ==> remove it ...
		m_data = nullptr;
	}
}

exml::Declaration::Declaration(const exml::Declaration& _obj) :
  exml::AttributeList(_obj.m_data) {
	
}

exml::Declaration::Declaration(const std::string& _name) :
  exml::AttributeList() {
	m_data = exml::internal::Declaration::create();
}

exml::Declaration& exml::Declaration::operator= (const exml::Declaration& _obj) {
	m_data = _obj.m_data;
	return *this;
}

//////////////////////////////////////////////////////////////////////////////////


exml::DeclarationXML::DeclarationXML(ememory::SharedPtr<exml::internal::Node> _internalNode) :
  exml::Declaration(_internalNode) {
	if (m_data == nullptr) {
		return;
	}
	// TODO: Do it better
	if (m_data->isDeclaration() == false) {
		// try to set wrong type inside ... ==> remove it ...
		m_data = nullptr;
	}
}

exml::DeclarationXML::DeclarationXML(const exml::DeclarationXML& _obj) :
  exml::Declaration(_obj.m_data) {
	
}

exml::DeclarationXML::DeclarationXML(const std::string& _version, const std::string& _format, bool _standalone) :
  exml::Declaration() {
	m_data = exml::internal::DeclarationXML::create(_version, _format, _standalone);
}

exml::DeclarationXML& exml::DeclarationXML::operator= (const exml::DeclarationXML& _obj) {
	m_data = _obj.m_data;
	return *this;
}




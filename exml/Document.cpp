/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <exml/Document.hpp>
#include <exml/debug.hpp>
#include <exml/internal/Document.hpp>

exml::Document::Document(ememory::SharedPtr<exml::internal::Node> _internalNode) :
  exml::Element(_internalNode) {
	if (m_data == nullptr) {
		return;
	}
	if (m_data->isDocument() == false) {
		// try to set wrong type inside ... ==> remove it ...
		m_data = nullptr;
	}
}

exml::Document::Document(const exml::Document& _obj) :
  exml::Element(_obj.m_data) {
	
}

exml::Document::Document() :
  exml::Element() {
	m_data = exml::internal::Document::create();
}

exml::Document& exml::Document::operator= (const exml::Document& _obj) {
	m_data = _obj.m_data;
	return *this;
}

bool exml::Document::parse(const std::string& _data) {
	if (m_data == nullptr) {
		EXML_DEBUG("Can not parse (nullptr) ...");
		return false;
	}
	return static_cast<exml::internal::Document*>(m_data.get())->parse(_data);
}

bool exml::Document::generate(std::string& _data) {
	if (m_data == nullptr) {
		EXML_DEBUG("Can not generate (nullptr) ...");
		return false;
	}
	return static_cast<exml::internal::Document*>(m_data.get())->generate(_data);
}

bool exml::Document::load(const std::string& _file) {
	if (m_data == nullptr) {
		EXML_DEBUG("Can not load (nullptr) ...");
		return false;
	}
	return static_cast<exml::internal::Document*>(m_data.get())->load(_file);
}

bool exml::Document::store(const std::string& _file) {
	if (m_data == nullptr) {
		EXML_DEBUG("Can not store (nullptr) ...");
		return false;
	}
	return static_cast<exml::internal::Document*>(m_data.get())->store(_file);
}

void exml::Document::display() {
	if (m_data == nullptr) {
		EXML_DEBUG("Can not display (nullptr) ...");
		return;
	}
	static_cast<exml::internal::Document*>(m_data.get())->display();
}

void exml::Document::setCaseSensitive(bool _val) {
	if (m_data == nullptr) {
		EXML_DEBUG("Can not setCaseSensitive (nullptr) ...");
		return;
	}
	static_cast<exml::internal::Document*>(m_data.get())->setCaseSensitive(_val);
}

bool exml::Document::getCaseSensitive() const {
	if (m_data == nullptr) {
		EXML_DEBUG("Can not getCaseSensitive (nullptr) ...");
		return false;
	}
	return static_cast<const exml::internal::Document*>(m_data.get())->getCaseSensitive();
}

void exml::Document::setDisplayError(bool _value){
	if (m_data == nullptr) {
		EXML_DEBUG("Can not setDisplayError (nullptr) ...");
		return;
	}
	static_cast<exml::internal::Document*>(m_data.get())->setDisplayError(_value);
}

bool exml::Document::getDisplayError() {
	if (m_data == nullptr) {
		EXML_DEBUG("Can not getDisplayError (nullptr) ...");
		return false;
	}
	return static_cast<exml::internal::Document*>(m_data.get())->getDisplayError();
}

void exml::Document::displayError() {
	if (m_data == nullptr) {
		EXML_DEBUG("Can not displayError (nullptr) ...");
		return;
	}
	static_cast<exml::internal::Document*>(m_data.get())->displayError();
}

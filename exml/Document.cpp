/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <exml/Document.h>
#include <exml/debug.h>
#include <exml/internal/Document.h>

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
		EXML_ERROR("Can not parse (nullptr) ...");
		return false;
	}
	return static_cast<exml::internal::Document*>(m_data.get())->parse(_data);
}

bool exml::Document::generate(std::string& _data) {
	if (m_data == nullptr) {
		EXML_ERROR("Can not generate (nullptr) ...");
		return false;
	}
	return static_cast<exml::internal::Document*>(m_data.get())->generate(_data);
}

bool exml::Document::load(const std::string& _file) {
	if (m_data == nullptr) {
		EXML_ERROR("Can not load (nullptr) ...");
		return false;
	}
	return static_cast<exml::internal::Document*>(m_data.get())->load(_file);
}

bool exml::Document::store(const std::string& _file) {
	if (m_data == nullptr) {
		EXML_ERROR("Can not store (nullptr) ...");
		return false;
	}
	return static_cast<exml::internal::Document*>(m_data.get())->store(_file);
}

void exml::Document::display() {
	if (m_data == nullptr) {
		EXML_ERROR("Can not display (nullptr) ...");
		return;
	}
	static_cast<exml::internal::Document*>(m_data.get())->display();
}

void exml::Document::displayError() {
	if (m_data == nullptr) {
		EXML_ERROR("Can not displayError (nullptr) ...");
		return;
	}
	static_cast<exml::internal::Document*>(m_data.get())->displayError();
}


void exml::Document::setCaseSensitive(bool _val) {
	if (m_data == nullptr) {
		EXML_ERROR("Can not setCaseSensitive (nullptr) ...");
		return;
	}
	static_cast<exml::internal::Document*>(m_data.get())->setCaseSensitive(_val);
}

bool exml::Document::getCaseSensitive() const {
	if (m_data == nullptr) {
		EXML_ERROR("Can not getCaseSensitive (nullptr) ...");
		return false;
	}
	return static_cast<exml::internal::Document*>(m_data.get())->getCaseSensitive();
}

void exml::Document::displayErrorWhenDetected() {
	if (m_data == nullptr) {
		EXML_ERROR("Can not displayErrorWhenDetected (nullptr) ...");
		return;
	}
	static_cast<exml::internal::Document*>(m_data.get())->displayErrorWhenDetected();
}

void exml::Document::notDisplayErrorWhenDetected() {
	if (m_data == nullptr) {
		EXML_ERROR("Can not notDisplayErrorWhenDetected (nullptr) ...");
		return;
	}
	static_cast<exml::internal::Document*>(m_data.get())->notDisplayErrorWhenDetected();
}



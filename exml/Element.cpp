/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <exml/Element.h>
#include <exml/debug.h>
#include <exml/internal/Element.h>


exml::Element::Element(ememory::SharedPtr<exml::internal::Node> _internalNode) :
  exml::AttributeList(_internalNode),
  nodes(this) {
	if (m_data == nullptr) {
		return;
	}
	if (    m_data->isElement() == false
	     && m_data->isDocument() == false) {
		// try to set wrong type inside ... ==> remove it ...
		m_data = nullptr;
	}
}

exml::Element::Element(const exml::Element& _obj) :
  exml::AttributeList(_obj.m_data),
  nodes(this) {
	
}

exml::Element::Element(const std::string& _data) :
  exml::AttributeList(),
  nodes(this) {
	m_data = exml::internal::Element::create(_data);
}

exml::Element& exml::Element::operator= (const exml::Element& _obj) {
	m_data = _obj.m_data;
	return *this;
}

exml::ElementData::iterator exml::ElementData::begin() {
	return exml::ElementData::iterator(*this, 0);
}

exml::ElementData::iterator exml::ElementData::end() {
	return exml::ElementData::iterator(*this, size());
}

const exml::ElementData::iterator exml::ElementData::begin() const {
	return exml::ElementData::iterator(*this, 0);
}

const exml::ElementData::iterator exml::ElementData::end() const {
	return exml::ElementData::iterator(*this, size());
}


exml::ElementData::ElementData(exml::Element* _elem) :
  m_data(_elem) {
	
}

size_t exml::ElementData::size() const {
	if (m_data->m_data == nullptr) {
		EXML_ERROR(" can not get type ...");
		return 0;
	}
	return static_cast<exml::internal::Element*>(m_data->m_data.get())->size();
}

enum exml::nodeType exml::ElementData::getType(int32_t _id) const {
	if (m_data->m_data == nullptr) {
		EXML_ERROR(" can not get type ...");
		return exml::nodeType::unknow;
	}
	return static_cast<exml::internal::Element*>(m_data->m_data.get())->getType(_id);
}

exml::Node exml::ElementData::operator[](int32_t _id) {
	if (m_data->m_data == nullptr) {
		EXML_ERROR(" can not get type ...");
		return exml::Node();
	}
	return exml::Node(static_cast<exml::internal::Element*>(m_data->m_data.get())->getNode(_id));
}

const exml::Node exml::ElementData::operator[](int32_t _id) const {
	if (m_data->m_data == nullptr) {
		EXML_ERROR(" can not get type ...");
		return exml::Node();
	}
	return exml::Node(static_cast<exml::internal::Element*>(m_data->m_data.get())->getNode(_id));
}

exml::Element exml::ElementData::operator[](const std::string& _name) {
	if (m_data->m_data == nullptr) {
		EXML_ERROR(" can not get type ...");
		return exml::Element();
	}
	return exml::Element(static_cast<exml::internal::Element*>(m_data->m_data.get())->getNamed(_name));
}

const exml::Element exml::ElementData::operator[] (const std::string& _name) const {
	if (m_data->m_data == nullptr) {
		EXML_ERROR(" can not get type ...");
		return exml::Element();
	}
	return exml::Element(static_cast<exml::internal::Element*>(m_data->m_data.get())->getNamed(_name));
}

void exml::ElementData::add(const exml::Node& _node) {
	if (m_data->m_data == nullptr) {
		EXML_ERROR(" can not APPEND on null element ...");
		return;
	}
	static_cast<exml::internal::Element*>(m_data->m_data.get())->append(_node.m_data);
}

void exml::ElementData::remove(const std::string& _nodeName) {
	if (m_data->m_data == nullptr) {
		EXML_ERROR(" can not APPEND on null element ...");
		return;
	}
	static_cast<exml::internal::Element*>(m_data->m_data.get())->remove(_nodeName);
}

std::string exml::Element::getText() const {
	if (m_data == nullptr) {
		EXML_ERROR(" can not APPEND on null element ...");
		return "";
	}
	return static_cast<exml::internal::Element*>(m_data.get())->getText();
}

void exml::Element::clear() {
	if (m_data == nullptr) {
		EXML_ERROR(" can not CLEAR on null element ...");
		return;
	}
	static_cast<exml::internal::Element*>(m_data.get())->clear();
}


#include <exml/details/iterator.hxx>

template class exml::iterator<exml::ElementData, exml::Node>;


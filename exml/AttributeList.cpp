/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <exml/debug.hpp>
#include <exml/AttributeList.hpp>
#include <exml/internal/AttributeList.hpp>


exml::AttributeList::AttributeList(const ememory::SharedPtr<exml::internal::Node>& _internalNode) :
  exml::Node(_internalNode),
  attributes(this) {
	
}

exml::AttributeList::AttributeList() :
  exml::Node(),
  attributes(this) {
	
}

exml::AttributeListData::AttributeListData(exml::AttributeList* _list) :
  m_data(_list) {
	
}

size_t exml::AttributeListData::size() const {
	if (m_data->m_data == null) {
		EXML_DEBUG(" can not sizeAttribute ...");
		return 0;
	}
	return static_cast<exml::internal::AttributeList*>(m_data->m_data.get())->sizeAttribute();
	
}

exml::Attribute exml::AttributeListData::operator[] (int32_t _id) {
	if (m_data->m_data == null) {
		EXML_DEBUG(" can not getAttr (null) ...");
		return exml::Attribute(ememory::SharedPtr<exml::internal::Attribute>(null));
	}
	return exml::Attribute(static_cast<exml::internal::AttributeList*>(m_data->m_data.get())->getAttr(_id));
}

const exml::Attribute exml::AttributeListData::operator[] (int32_t _id) const {
	if (m_data->m_data == null) {
		EXML_DEBUG(" can not getAttr (null) ...");
		return exml::Attribute(ememory::SharedPtr<exml::internal::Attribute>(null));
	}
	return exml::Attribute(static_cast<exml::internal::AttributeList*>(m_data->m_data.get())->getAttr(_id));
}

etk::Pair<etk::String, etk::String> exml::AttributeListData::getPair(int32_t _id) const {
	if (m_data->m_data == null) {
		EXML_DEBUG(" can not getAttrPair (null) ...");
		return etk::Pair<etk::String, etk::String>("","");
	}
	return static_cast<exml::internal::AttributeList*>(m_data->m_data.get())->getAttrPair(_id);
}

void exml::AttributeListData::add(exml::Attribute _attr) {
	if (m_data->m_data == null) {
		EXML_DEBUG(" can not appendAttribute (null) ...");
		return;
	}
	static_cast<exml::internal::AttributeList*>(m_data->m_data.get())->appendAttribute(_attr.getInternalAttribute());
}

const etk::String& exml::AttributeListData::operator[](const etk::String& _name) const {
	if (m_data->m_data == null) {
		EXML_DEBUG(" can not getAttribute (null) ...");
		static etk::String errorValue("");
		return errorValue;
	}
	return static_cast<exml::internal::AttributeList*>(m_data->m_data.get())->getAttribute(_name);
}

bool exml::AttributeListData::exist(const etk::String& _name) const {
	if (m_data->m_data == null) {
		EXML_DEBUG(" can not getAttribute (null) ...");
		return false;
	}
	return static_cast<exml::internal::AttributeList*>(m_data->m_data.get())->existAttribute(_name);
}

bool exml::AttributeListData::remove(const etk::String& _name) {
	if (m_data->m_data == null) {
		EXML_DEBUG(" can not removeAttribute (null) ...");
		return false;
	}
	return static_cast<exml::internal::AttributeList*>(m_data->m_data.get())->removeAttribute(_name);
}

void exml::AttributeListData::set(const etk::String& _name, const etk::String& _value) {
	if (m_data->m_data == null) {
		EXML_DEBUG(" can not setAttribute (null) ...");
		return;
	}
	static_cast<exml::internal::AttributeList*>(m_data->m_data.get())->setAttribute(_name, _value);
}

#include <exml/details/iterator.hxx>

template class exml::iterator<exml::AttributeListData, exml::Attribute>;

exml::AttributeListData::iterator exml::AttributeListData::begin() {
	return exml::AttributeListData::iterator(*this, 0);
}

exml::AttributeListData::iterator exml::AttributeListData::end() {
	return exml::AttributeListData::iterator(*this, size());
}

const exml::AttributeListData::iterator exml::AttributeListData::begin() const {
	return exml::AttributeListData::iterator(*this, 0);
}

const exml::AttributeListData::iterator exml::AttributeListData::end() const {
	return exml::AttributeListData::iterator(*this, size());
}


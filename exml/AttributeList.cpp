/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <exml/debug.h>
#include <exml/AttributeList.h>
#include <exml/internal/AttributeList.h>


exml::AttributeList::AttributeList(ememory::SharedPtr<exml::internal::Node> _internalNode) :
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
	if (m_data->m_data == nullptr) {
		EXML_ERROR(" can not sizeAttribute ...");
		return 0;
	}
	return static_cast<exml::internal::AttributeList*>(m_data->m_data.get())->sizeAttribute();
	
}

exml::Attribute exml::AttributeListData::operator[] (int32_t _id) {
	if (m_data->m_data == nullptr) {
		EXML_ERROR(" can not getAttr (nullptr) ...");
		return exml::Attribute(ememory::SharedPtr<exml::internal::Attribute>(nullptr));
	}
	return exml::Attribute(static_cast<exml::internal::AttributeList*>(m_data->m_data.get())->getAttr(_id));
}

const exml::Attribute exml::AttributeListData::operator[] (int32_t _id) const {
	if (m_data->m_data == nullptr) {
		EXML_ERROR(" can not getAttr (nullptr) ...");
		return exml::Attribute(ememory::SharedPtr<exml::internal::Attribute>(nullptr));
	}
	return exml::Attribute(static_cast<exml::internal::AttributeList*>(m_data->m_data.get())->getAttr(_id));
}

std::pair<std::string, std::string> exml::AttributeListData::getPair(int32_t _id) const {
	if (m_data->m_data == nullptr) {
		EXML_ERROR(" can not getAttrPair (nullptr) ...");
		return std::pair<std::string, std::string>();
	}
	return static_cast<exml::internal::AttributeList*>(m_data->m_data.get())->getAttrPair(_id);
}

void exml::AttributeListData::add(exml::Attribute _attr) {
	if (m_data->m_data == nullptr) {
		EXML_ERROR(" can not appendAttribute (nullptr) ...");
		return;
	}
	static_cast<exml::internal::AttributeList*>(m_data->m_data.get())->appendAttribute(_attr.getInternalAttribute());
}

const std::string& exml::AttributeListData::get(const std::string& _name) const {
	if (m_data->m_data == nullptr) {
		EXML_ERROR(" can not getAttribute (nullptr) ...");
		static std::string errorValue("");
		return errorValue;
	}
	return static_cast<exml::internal::AttributeList*>(m_data->m_data.get())->getAttribute(_name);
}

bool exml::AttributeListData::exist(const std::string& _name) const {
	if (m_data->m_data == nullptr) {
		EXML_ERROR(" can not getAttribute (nullptr) ...");
		return false;
	}
	return static_cast<exml::internal::AttributeList*>(m_data->m_data.get())->existAttribute(_name);
}

bool exml::AttributeListData::remove(const std::string& _name) {
	if (m_data->m_data == nullptr) {
		EXML_ERROR(" can not removeAttribute (nullptr) ...");
		return false;
	}
	return static_cast<exml::internal::AttributeList*>(m_data->m_data.get())->removeAttribute(_name);
}

void exml::AttributeListData::set(const std::string& _name, const std::string& _value) {
	if (m_data->m_data == nullptr) {
		EXML_ERROR(" can not setAttribute (nullptr) ...");
		return;
	}
	static_cast<exml::internal::AttributeList*>(m_data->m_data.get())->setAttribute(_name, _value);
}

#include <exml/details/iterator.hxx>

template class exml::iterator<exml::AttributeListData, exml::Attribute>;



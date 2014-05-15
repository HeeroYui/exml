/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <exml/AttributeList.h>
#include <exml/debug.h>

#undef __class__
#define __class__ "AttributeList"

exml::AttributeList::~AttributeList() {
	for (size_t iii=0; iii<m_listAttribute.size(); iii++) {
		if (NULL!=m_listAttribute[iii]) {
			delete(m_listAttribute[iii]);
			m_listAttribute[iii]=NULL;
		}
	}
	m_listAttribute.clear();
}

exml::Attribute* exml::AttributeList::getAttr(int32_t _id) {
	if (_id <0 || (size_t)_id>m_listAttribute.size()) {
		return NULL;
	}
	return m_listAttribute[_id];
}

const exml::Attribute* exml::AttributeList::getAttr(int32_t _id) const {
	if (_id <0 || (size_t)_id>m_listAttribute.size()) {
		return NULL;
	}
	return m_listAttribute[_id];
}

void exml::AttributeList::appendAttribute(exml::Attribute* _attr) {
	if (_attr == NULL) {
		EXML_ERROR("Try to set an empty node");
		return;
	}
	for (size_t iii=0; iii<m_listAttribute.size(); iii++) {
		if (m_listAttribute[iii] == _attr) {
			EXML_ERROR("Try to add a node that is already added befor !!!");
			return;
		}
	}
	m_listAttribute.push_back(_attr);
}

const std::string& exml::AttributeList::getAttribute(const std::string& _name) const {
	static const std::string errorReturn("");
	if (_name.size() == 0) {
		return errorReturn;
	}
	for (size_t iii=0; iii<m_listAttribute.size(); iii++) {
		if(    NULL != m_listAttribute[iii]
		    && m_listAttribute[iii]->getName() == _name) {
			return m_listAttribute[iii]->getValue();
		}
	}
	return errorReturn;
}


bool exml::AttributeList::existAttribute(const std::string& _name) const {
	if (_name.size() == 0) {
		return false;
	}
	for (size_t iii=0; iii<m_listAttribute.size(); iii++) {
		if(    NULL != m_listAttribute[iii]
		    && m_listAttribute[iii]->getName() == _name) {
			return true;
		}
	}
	return false;
}

void exml::AttributeList::setAttribute(const std::string& _name, const std::string& _value) {
	// check if attribute already det :
	for (size_t iii=0; iii<m_listAttribute.size(); iii++) {
		if(    NULL != m_listAttribute[iii]
		    && m_listAttribute[iii]->getName() == _name) {
			// update the value :
			m_listAttribute[iii]->setValue(_value);
			return;
		}
	}
	exml::Attribute* attr = new exml::Attribute(_name, _value);
	if (NULL == attr) {
		EXML_ERROR("memory allocation error...");
	}
	m_listAttribute.push_back(attr);
}

bool exml::AttributeList::iGenerate(std::string& _data, int32_t _indent) const {
	for (size_t iii=0; iii<m_listAttribute.size(); iii++) {
		if (NULL!=m_listAttribute[iii]) {
			m_listAttribute[iii]->iGenerate(_data, _indent);
		}
	}
	return true;
}

void exml::AttributeList::clear() {
	exml::Node::clear();
	for (size_t iii=0; iii<m_listAttribute.size(); iii++) {
		if (NULL!=m_listAttribute[iii]) {
			delete(m_listAttribute[iii]);
			m_listAttribute[iii]=NULL;
		}
	}
	m_listAttribute.clear();
}



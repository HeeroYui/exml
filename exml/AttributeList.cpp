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
#define __class__	"AttributeList"

exml::AttributeList::~AttributeList(void)
{
	for (int32_t iii=0; iii<m_listAttribute.Size(); iii++) {
		if (NULL!=m_listAttribute[iii]) {
			delete(m_listAttribute[iii]);
			m_listAttribute[iii]=NULL;
		}
	}
	m_listAttribute.Clear();
}

exml::Attribute* exml::AttributeList::GetAttr(int32_t _id)
{
	if (_id <0 || _id>m_listAttribute.Size()) {
		return NULL;
	}
	return m_listAttribute[_id];
}

const exml::Attribute* exml::AttributeList::GetAttr(int32_t _id) const
{
	if (_id <0 || _id>m_listAttribute.Size()) {
		return NULL;
	}
	return m_listAttribute[_id];
}

void exml::AttributeList::AppendAttribute(exml::Attribute* _attr)
{
	if (_attr == NULL) {
		EXML_ERROR("Try to set an empty node");
		return;
	}
	for (int32_t iii=0; iii<m_listAttribute.Size(); iii++) {
		if (m_listAttribute[iii] == _attr) {
			EXML_ERROR("Try to add a node that is already added befor !!!");
			return;
		}
	}
	m_listAttribute.PushBack(_attr);
}

const etk::UString& exml::AttributeList::GetAttribute(const etk::UString& _name) const
{
	static const etk::UString errorReturn("");
	if (_name.Size()==0) {
		return errorReturn;
	}
	for (int32_t iii=0; iii<m_listAttribute.Size(); iii++) {
		if(    NULL != m_listAttribute[iii]
		    && m_listAttribute[iii]->GetName() == _name) {
			return m_listAttribute[iii]->GetValue();
		}
	}
	return errorReturn;
}

bool exml::AttributeList::ExistAttribute(const etk::UString& _name) const
{
	if (_name.Size()==0) {
		return false;
	}
	for (int32_t iii=0; iii<m_listAttribute.Size(); iii++) {
		if(    NULL != m_listAttribute[iii]
		    && m_listAttribute[iii]->GetName() == _name) {
			return true;
		}
	}
	return false;
}

void exml::AttributeList::SetAttribute(const etk::UString& _name, const etk::UString& _value)
{
	// check if attribute already det :
	for (int32_t iii=0; iii<m_listAttribute.Size(); iii++) {
		if(    NULL != m_listAttribute[iii]
		    && m_listAttribute[iii]->GetName() == _name) {
			// update the value :
			m_listAttribute[iii]->SetValue(_value);
			return;
		}
	}
	exml::Attribute* attr = new exml::Attribute(_name, _value);
	if (NULL==attr) {
		EXML_ERROR("memory allocation error...");
	}
	m_listAttribute.PushBack(attr);
}

bool exml::AttributeList::IGenerate(etk::UString& _data, int32_t _indent) const
{
	for (int32_t iii=0; iii<m_listAttribute.Size(); iii++) {
		if (NULL!=m_listAttribute[iii]) {
			m_listAttribute[iii]->IGenerate(_data, _indent);
		}
	}
	return true;
}

void exml::AttributeList::Clear(void)
{
	exml::Node::Clear();
	for (int32_t iii=0; iii<m_listAttribute.Size(); iii++) {
		if (NULL!=m_listAttribute[iii]) {
			delete(m_listAttribute[iii]);
			m_listAttribute[iii]=NULL;
		}
	}
	m_listAttribute.Clear();
}



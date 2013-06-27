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

void exml::AttributeList::AppendAttribute(exml::Attribute* _node)
{
	if (_node == NULL) {
		EXML_ERROR("Try to set an empty node");
		return;
	}
	for (int32_t iii=0; iii<m_listAttribute.Size(); iii++) {
		if (m_listAttribute[iii] == _node) {
			EXML_ERROR("Try to add a node that is already added befor !!!");
			return;
		}
	}
	m_listAttribute.PushBack(_node);
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

bool exml::AttributeList::Generate(etk::UString& _data, int32_t _indent) const
{
	for (int32_t iii=0; iii<m_listAttribute.Size(); iii++) {
		if (NULL!=m_listAttribute[iii]) {
			m_listAttribute[iii]->Generate(_data, _indent);
		}
	}
	return true;
}

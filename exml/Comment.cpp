/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <exml/Comment.hpp>
#include <exml/debug.hpp>
#include <exml/internal/Comment.hpp>

exml::Comment::Comment(ememory::SharedPtr<exml::internal::Node> _internalNode) :
  exml::Node(_internalNode) {
	if (m_data == null) {
		return;
	}
	if (m_data->isComment() == false) {
		// try to set wrong type inside ... ==> remove it ...
		m_data = null;
	}
}

exml::Comment::Comment(const exml::Comment& _obj) :
  exml::Node(_obj.m_data) {
	
}

exml::Comment::Comment(const etk::String& _value) :
  exml::Node() {
	m_data = exml::internal::Comment::create(_value);
}

exml::Comment& exml::Comment::operator= (const exml::Comment& _obj) {
	m_data = _obj.m_data;
	return *this;
}

/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <exml/Text.hpp>
#include <exml/internal/Text.hpp>
#include <exml/debug.hpp>

exml::Text::Text(ememory::SharedPtr<exml::internal::Node> _internalNode) :
  exml::Node(_internalNode) {
	if (m_data == null) {
		return;
	}
	if (m_data->isText() == false) {
		// try to set wrong type inside ... ==> remove it ...
		m_data = null;
	}
}

exml::Text::Text(const exml::Text& _obj) :
  exml::Node(_obj.m_data) {
	
}

exml::Text::Text(const etk::String& _data) :
  exml::Node() {
	m_data = exml::internal::Text::create(_data);
}

exml::Text& exml::Text::operator= (const exml::Text& _obj) {
	m_data = _obj.m_data;
	return *this;
}


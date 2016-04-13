/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <exml/nodeType.h>
#include <exml/debug.h>



std::ostream& exml::operator <<(std::ostream& _os, enum exml::nodeType _obj) {
	switch (_obj) {
		case nodeType_unknow:
			_os << "exml::nodeType_unknow";
			break;
		case nodeType_node:
			_os << "exml::nodeType_node";
			break;
		case nodeType_document:
			_os << "exml::nodeType_document";
			break;
		case nodeType_declaration:
			_os << "exml::nodeType_declaration";
			break;
		case nodeType_attribute:
			_os << "exml::nodeType_attribute";
			break;
		case nodeType_element:
			_os << "exml::nodeType_element";
			break;
		case nodeType_comment:
			_os << "exml::nodeType_comment";
			break;
		case nodeType_text:
			_os << "exml::nodeType_text";
			break;
	}
	return _os;
}


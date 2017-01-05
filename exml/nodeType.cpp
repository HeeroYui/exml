/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <exml/nodeType.hpp>
#include <exml/debug.hpp>



std::ostream& exml::operator <<(std::ostream& _os, enum exml::nodeType _obj) {
	switch (_obj) {
		case nodeType::unknow:
			_os << "exml::nodeType::unknow";
			break;
		case nodeType::node:
			_os << "exml::nodeType::node";
			break;
		case nodeType::document:
			_os << "exml::nodeType::document";
			break;
		case nodeType::declaration:
			_os << "exml::nodeType::declaration";
			break;
		case nodeType::attribute:
			_os << "exml::nodeType::attribute";
			break;
		case nodeType::element:
			_os << "exml::nodeType::element";
			break;
		case nodeType::comment:
			_os << "exml::nodeType::comment";
			break;
		case nodeType::text:
			_os << "exml::nodeType::text";
			break;
	}
	return _os;
}


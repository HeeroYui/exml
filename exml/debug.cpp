/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <exml/debug.h>

int32_t exml::getLogId() {
	static int32_t g_val = etk::log::registerInstance("exml");
	return g_val;
}


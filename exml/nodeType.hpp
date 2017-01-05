/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <ostream>

/**
 * @brief exml namespace containing all function for XML interpretor
 */
namespace exml {
	/**
	 * @brief Type of the XML elements.
	 */
	enum class nodeType {
		unknow, //!< might be an error ...
		node, //!< might be an error ...
		document, //!< all the file main access
		declaration, //!< &lt;?xml ... ?&gt;
		attribute, //!< the &lt;Element ATTRIBUTE="ATTRIBUTE_VALUE" /&gt;
		element,  //!< the &lt;XXX&gt; ... &lt;/XXX&gt;
		comment, //!< comment node : &lt;!--   --&gt;
		text, //!< &lt;XXX&gt; InsideText &lt;/XXX&gt;
	};
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, enum nodeType _obj);
}


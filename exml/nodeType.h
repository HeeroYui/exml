/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
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
	enum nodeType {
		nodeType_unknow, //!< might be an error ...
		nodeType_node, //!< might be an error ...
		nodeType_document, //!< all the file main access
		nodeType_declaration, //!< &lt;?xml ... ?&gt;
		nodeType_attribute, //!< the &lt;Element ATTRIBUTE="ATTRIBUTE_VALUE" /&gt;
		nodeType_element,  //!< the &lt;XXX&gt; ... &lt;/XXX&gt;
		nodeType_comment, //!< comment node : &lt;!--   --&gt;
		nodeType_text, //!< &lt;XXX&gt; InsideText &lt;/XXX&gt;
	};
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, enum nodeType _obj);
}


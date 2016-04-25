/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <exml/Node.h>
#include <vector>

namespace exml {
	/**
	 * @brief Text node interface (internal data between two balise : &lt;XXX&gt; ALL here &lt;/XXX&gt;
	 */
	class Text : public exml::Node {
		public:
			/**
			 * @brief Constructor
			 * @param[in] _internalNode Internal Node to set data
			 */
			Text(ememory::SharedPtr<exml::internal::Node> _internalNode);
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 */
			Text(const exml::Text& _obj);
			/**
			 * @brief Constructor
			 * @param[in] _data String data of the current Text
			 */
			Text(const std::string& _data="");
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 * @return A reference on this object
			 */
			exml::Text& operator= (const exml::Text& _obj);
	};
}


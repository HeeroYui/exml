/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <exml/Node.hpp>
#include <etk/Vector.hpp>

namespace exml {
	/**
	 * @brief Comment node: &lt;!-- ... --&gt;
	 */
	class Comment : public exml::Node {
		public:
			/**
			 * @brief Constructor
			 * @param[in] _internalNode Internal Node to set data
			 */
			Comment(ememory::SharedPtr<exml::internal::Node> _internalNode);
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 */
			Comment(const exml::Comment& _obj);
			/**
			 * @brief Constructor
			 * @param[in] _value comment value
			 */
			Comment(const etk::String& _value="");
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 * @return A reference on the local Object
			 */
			exml::Comment& operator= (const exml::Comment& _obj);
	};
}


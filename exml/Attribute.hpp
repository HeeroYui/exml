/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <exml/Node.hpp>
#include <etk/Vector.hpp>
#include <etk/Pair.hpp>

namespace exml {
	namespace internal {
		class Attribute;
	}
	class AttributeListData;
	/**
	 * @brief Single attribute element
	 */
	class Attribute : public exml::Node {
		public:
			/**
			 * @brief Constructor
			 * @param[in] _internalNode Internal Node to set data
			 */
			Attribute(ememory::SharedPtr<exml::internal::Node> _internalNode);
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 */
			// TODO : Attribute(null);
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 */
			Attribute(const exml::Attribute& _obj);
			/**
			 * @brief Constructor
			 * @param[in] _name Name of the attribute.
			 * @param[in] _value Value of the attribute.
			 */
			Attribute(const etk::String& _name="", const etk::String& _value="");
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 * @return Local reference on this object
			 */
			exml::Attribute& operator= (const exml::Attribute& _obj);
		public:
			/**
			 * @brief set the name of the attribute
			 * @param[in] _name New name of the attribute
			 */
			virtual void setName(const etk::String& _name);
			/**
			 * @brief get the current name of the Attribute
			 * @return String of the attribute
			 */
			virtual const etk::String& getName() const;
			/**
			 * @brief get attribute name and value
			 * @return Name and value of the attribute
			 */
			etk::Pair<etk::String, etk::String> getPair() const;
		public:
			void clear() override;
		friend class exml::AttributeListData;
		private:
			ememory::SharedPtr<exml::internal::Attribute> getInternalAttribute();
	};
}


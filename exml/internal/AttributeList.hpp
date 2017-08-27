/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <exml/internal/Node.hpp>
#include <etk/Vector.hpp>
#include <exml/internal/Attribute.hpp>
#include <utility>

namespace exml {
	namespace internal {
		/**
		 * @brief List of all attribute element in a node
		 */
		class AttributeList : public exml::internal::Node {
			protected:
				/**
				 * @brief Constructor
				 * @param[in] _value Node value;
				 */
				AttributeList(const etk::String& _value="") :
				  exml::internal::Node(_value) {
					
				};
			protected:
				etk::Vector<ememory::SharedPtr<exml::internal::Attribute>> m_listAttribute; //!< list of all attribute
			public:
				/**
				 * @brief get the number of attribute in the Node
				 * @return Nulber of attribute >=0
				 */
				size_t sizeAttribute() const {
					return m_listAttribute.size();
				};
				/**
				 * @brief add attribute on the List
				 * @param[in] _attr Pointer on the attribute
				 */
				void appendAttribute(const ememory::SharedPtr<exml::internal::Attribute>& _attr);
				/**
				 * @brief get attribute whith his ID
				 * @param[in] _id Identifier of the attribute 0<= _id < sizeAttribute()
				 * @return Pointer on the attribute or NULL
				 */
				ememory::SharedPtr<Attribute> getAttr(int32_t _id);
				/**
				 * @brief get attribute whith his ID
				 * @param[in] _id Identifier of the attribute 0<= _id < sizeAttribute()
				 * @return Pointer on the attribute or NULL
				 */
				ememory::SharedPtr<const Attribute> getAttr(int32_t _id) const;
				/**
				 * @brief get attribute whith his ID
				 * @param[in] _id Identifier of the attribute 0<= _id < sizeAttribute()
				 * @return Name and value of the attribute
				 */
				etk::Pair<etk::String, etk::String> getAttrPair(int32_t _id) const;
				/**
				 * @brief get the attribute value with searching in the List with his name
				 * @param[in] _name Attribute Name.
				 * @return Value of the attribute or no data in the string
				 */
				const etk::String& getAttribute(const etk::String& _name) const;
				/**
				 * @brief check if an attribute exist or not with his name.
				 * @param[in] _name Attribute Name.
				 * @return true if the attribute exist or False
				 */
				bool existAttribute(const etk::String& _name) const;
				/**
				 * @brief Set A new attribute or replace data of the previous one
				 * @param[in] _name Name of the attribute
				 * @param[in] _value Value of the attribute
				 */
				void setAttribute(const etk::String& _name, const etk::String& _value);
				/**
				 * @brief Remove an attribute form the list
				 * @param[in] _name Name of the attribute
				 * @return true The attribute has been removed
				 * @return false An error occured.
				 */
				bool removeAttribute(const etk::String& _name);
			public:
				bool iGenerate(etk::String& _data, int32_t _indent) const override;
				void clear() override;
		};
	}
}


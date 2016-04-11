/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <exml/Node.h>
#include <vector>
#include <exml/Attribute.h>
#include <utility>

namespace exml {
	class AttributeList : public exml::Node {
		protected:
			/**
			 * @brief Constructor
			 * @param[in] _value Node value;
			 */
			AttributeList(const std::string& _value="") :
			  exml::Node(_value) {
				
			};
		protected:
			std::vector<ememory::SharedPtr<exml::Attribute>> m_listAttribute; //!< list of all attribute
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
			void appendAttribute(const ememory::SharedPtr<exml::Attribute>& _attr);
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
			std::pair<std::string, std::string> getAttrPair(int32_t _id) const;
			/**
			 * @brief get the attribute value with searching in the List with his name
			 * @param[in] _name Attribute Name.
			 * @return Value of the attribute or no data in the string
			 */
			const std::string& getAttribute(const std::string& _name) const;
			/**
			 * @brief check if an attribute exist or not with his name.
			 * @param[in] _name Attribute Name.
			 * @return true if the attribute exist or False
			 */
			bool existAttribute(const std::string& _name) const;
			/**
			 * @brief Set A new attribute or replace data of the previous one
			 * @param[in] _name Name of the attribute
			 * @param[in] _value Value of the attribute
			 */
			void setAttribute(const std::string& _name, const std::string& _value);
			/**
			 * @brief Remove an attribute form the list
			 * @param[in] _name Name of the attribute
			 * @return true The attribute has been removed
			 * @return false An error occured.
			 */
			bool removeAttribute(const std::string& _name);
		public:
			bool iGenerate(std::string& _data, int32_t _indent) const override;
			void clear() override;
	};
}


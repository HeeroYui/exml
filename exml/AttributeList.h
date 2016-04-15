/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <exml/Node.h>
#include <exml/Attribute.h>
#include <exml/iterator.h>

namespace exml {
	class AttributeList;
	
	class AttributeListData {
		private:
			exml::AttributeList* m_data;
		public:
			AttributeListData(exml::AttributeList* _list);
		public:
			/**
			 * @brief get the number of attribute in the Node
			 * @return Number of attribute >=0
			 */
			size_t size() const;
			/**
			 * @brief add attribute on the List
			 * @param[in] _attr Pointer on the attribute
			 */
			void add(exml::Attribute _attr);
			/**
			 * @brief Remove an attribute form the list
			 * @param[in] _name Name of the attribute
			 * @return true The attribute has been removed
			 * @return false An error occured.
			 */
			bool remove(const std::string& _name);
			/**
			 * @brief get attribute whith his ID
			 * @param[in] _id Identifier of the attribute 0<= _id < sizeAttribute()
			 * @return Pointer on the attribute or NULL
			 */
			exml::Attribute operator[] (int32_t _id);
			/**
			 * @brief get attribute whith his ID
			 * @param[in] _id Identifier of the attribute 0<= _id < sizeAttribute()
			 * @return Pointer on the attribute or NULL
			 */
			const exml::Attribute operator[](int32_t _id) const;
			/**
			 * @brief get attribute whith his ID
			 * @param[in] _id Identifier of the attribute 0<= _id < sizeAttribute()
			 * @return Name and value of the attribute
			 */
			std::pair<std::string, std::string> getPair(int32_t _id) const;
			/**
			 * @brief get the attribute value with searching in the List with his name
			 * @param[in] _name Attribute Name.
			 * @return Value of the attribute or no data in the string
			 */
			const std::string& operator[](const std::string& _name) const;
			/**
			 * @brief check if an attribute exist or not with his name.
			 * @param[in] _name Attribute Name.
			 * @return true if the attribute exist or False
			 */
			bool exist(const std::string& _name) const;
			/**
			 * @brief Set A new attribute or replace data of the previous one
			 * @param[in] _name Name of the attribute
			 * @param[in] _value Value of the attribute
			 */
			void set(const std::string& _name, const std::string& _value);
		public:
			using iterator = exml::iterator<exml::AttributeListData, exml::Attribute>;
			iterator begin() {
				return iterator(*this, 0);
			}
			iterator end() {
				return iterator(*this, size());
			}
	};
	
	/**
	 * @brief List of all attribute element in a node
	 */
	class AttributeList : public exml::Node {
		public:
			AttributeListData attributes;
		protected:
			/**
			 * @brief basic element of a xml structure
			 * @param[in] _value value of the node
			 */
			AttributeList(ememory::SharedPtr<exml::internal::Node> _internalNode);
			/**
			 * @brief basic element of a xml structure
			 */
			AttributeList();
	};
}


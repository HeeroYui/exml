/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <exml/Node.hpp>
#include <exml/Attribute.hpp>
#include <exml/iterator.hpp>

namespace exml {
	class AttributeList;
	/**
	 * @brief Abstract interface on all attributes elements
	 */
	class AttributeListData {
		private:
			exml::AttributeList* m_data; //!< Pointer on the Attribute list class (must not be nullptr)
		public:
			/**
			 * @brief Constructor on the AttributeListData class
			 * @param[in] _list Point on the parrent class (must not be nullptr)
			 */
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
			using iterator = exml::iterator<exml::AttributeListData, exml::Attribute>; //!< Specify iterator of the element methode
			/**
			 * @brief Get iterator of the first sub nodes
			 * @return iterator on the begin position of the nodes
			 */
			iterator begin();
			/**
			 * @brief Get iterator of the next of the last sub nodes
			 * @return iterator on the next of the last position of the nodes
			 */
			iterator end();
			/**
			 * @brief Get const iterator of the first sub nodes
			 * @return const iterator on the begin position of the nodes
			 */
			const iterator begin() const;
			/**
			 * @brief Get const iterator of the next of the last sub nodes
			 * @return const iterator on the next of the last position of the nodes
			 */
			const iterator end() const;
	};
	
	/**
	 * @brief List of all attribute element in a node
	 */
	class AttributeList : public exml::Node {
		public:
			AttributeListData attributes; //!< interface on all attributes
		protected:
			/**
			 * @brief basic element of a xml structure
			 * @param[in] _internalNode Value of the node
			 */
			AttributeList(const ememory::SharedPtr<exml::internal::Node>& _internalNode);
			/**
			 * @brief basic element of a xml structure
			 */
			AttributeList();
	};
}


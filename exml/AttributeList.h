/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ETK_XML_ATTRIBUTE_LIST_H__
#define __ETK_XML_ATTRIBUTE_LIST_H__

#include <exml/Node.h>
#include <vector>
#include <exml/Attribute.h>
#include <utility>

namespace exml {
	class AttributeList : public exml::Node {
		protected:
			/**
			 * @brief Constructor
			 */
			AttributeList() { };
			/**
			 * @brief Constructor
			 * @param[in] _value Node value;
			 */
			AttributeList(const std::string& _value) :
			  exml::Node(_value) {
				
			};
		public:
			/**
			 * @brief Destructor
			 */
			virtual ~AttributeList();
		protected:
			std::vector<std::shared_ptr<exml::Attribute>> m_listAttribute; //!< list of all attribute
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
			void appendAttribute(const std::shared_ptr<exml::Attribute>& _attr);
			/**
			 * @brief get attribute whith his ID
			 * @param[in] _id Identifier of the attribute 0<= _id < sizeAttribute()
			 * @return Pointer on the attribute or NULL
			 */
			std::shared_ptr<Attribute> getAttr(int32_t _id);
			std::shared_ptr<const Attribute> getAttr(int32_t _id) const;
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
			 * @brief Sen A new attribute or replace data of the previous one
			 * @param[in] _name Name of the attribute
			 * @param[in] _value Value of the attribute
			 */
			void setAttribute(const std::string& _name, const std::string& _value);
		public: // herited function:
			bool iGenerate(std::string& _data, int32_t _indent) const;
			virtual void clear();
	};
};


#endif


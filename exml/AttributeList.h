/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_XML_ATTRIBUTE_LIST_H__
#define __ETK_XML_ATTRIBUTE_LIST_H__

#include <exml/Node.h>
#include <etk/Vector.h>
#include <exml/Attribute.h>

namespace exml
{
	class AttributeList : public Node
	{
		public:
			/**
			 * @brief Constructor
			 */
			AttributeList(void) { };
			/**
			 * @brief Constructor
			 * @param[in] _value Node value;
			 */
			AttributeList(const etk::UString& _value) : exml::Node(_value) { };
			/**
			 * @brief Destructor
			 */
			virtual ~AttributeList(void);
		protected:
			etk::Vector<exml::Attribute*> m_listAttribute; //!< list of all attribute
		public:
			/**
			 * @brief Get the number of attribute in the Node
			 * @return Nulber of attribute >=0
			 */
			int32_t SizeAttribute(void) const { return m_listAttribute.Size(); };
			/**
			 * @brief Add attribute on the List
			 * @param[in] _attr Pointer on the attribute
			 */
			void AppendAttribute(exml::Attribute* _attr);
			/**
			 * @brief Get attribute whith his ID
			 * @param[in] _id Identifier of the attribute 0<= _id < SizeAttribute()
			 * @return Pointer on the attribute or NULL
			 */
			Attribute* GetAttr(int32_t _id);
			const Attribute* GetAttr(int32_t _id) const;
			/**
			 * @brief Get the attribute value with searching in the List with his name
			 * @param[in] _name Attribute Name.
			 * @return Value of the attribute or no data in the string
			 */
			const etk::UString& GetAttribute(const etk::UString& _name) const;
			/**
			 * @brief Check if an attribute Exist or not with his name.
			 * @param[in] _name Attribute Name.
			 * @return true if the attribute exist or False
			 */
			bool ExistAttribute(const etk::UString& _name) const;
			/**
			 * @brief Sen A new attribute or replace data of the previous one
			 * @param[in] _name Name of the attribute
			 * @param[in] _value Value of the attribute
			 */
			void SetAttribute(const etk::UString& _name, const etk::UString& _value);
		public: // herited function:
			bool Generate(etk::UString& _data, int32_t _indent) const;
			virtual void Clear(void);
	};
};


#endif


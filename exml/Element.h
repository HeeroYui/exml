/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_XML_ELEMENT_H__
#define __ETK_XML_ELEMENT_H__

#include <exml/Node.h>
#include <etk/Vector.h>
#include <exml/AttributeList.h>

namespace exml
{
	class Element : public AttributeList
	{
		public:
			/**
			 * @brief Constructor
			 */
			Element(void) { };
			/**
			 * @brief Constructor
			 * @param[in] _value Element name;
			 */
			Element(const etk::UString& _value) : exml::AttributeList(_value) { };
			/**
			 * @brief Destructor
			 */
			virtual ~Element(void);
		protected:
			etk::Vector<exml::Node*> m_listSub;
		public:
			/**
			 * @brief Get the number of sub element in the node (can be exml::Comment ; exml::Element ; exml::Text :exml::Declaration).
			 * @return a number >=0.
			 */
			int32_t Size(void) const { return m_listSub.Size(); };
			/**
			 * @brief Add a node at the element (not exml::Attribute (move in the attribute automaticly).
			 * @param[in] _node Pointer of the node to add.
			 */
			void Append(Node* _node);
			/**
			 * @brief Get the type of the element id.
			 * @param[in] _id Id of the element.
			 * @return the Current type of the element or exml::typeUnknow.
			 */
			      nodeType_te GetType(int32_t _id);
			const nodeType_te GetType(int32_t _id) const;
			/**
			 * @brief Get the Node pointer of the element id.
			 * @param[in] _id Id of the element.
			 * @return Pointer on node.
			 */
			      Node* GetNode(int32_t _id);
			const Node* GetNode(int32_t _id) const;
			/**
			 * @brief Get the element casted in Element (if the node is not an element return NULL).
			 * @param[in] _id Id of the element.
			 * @return Pointer on the element or NULL.
			 */
			      Element* GetElement(int32_t _id);
			const Element* GetElement(int32_t _id) const;
			/**
			 * @brief Get an element with his name (work only with exml::Element)
			 * @param[in] _name Name of the element that is requested
			 * @return Pointer on the element or NULL.
			 */
			      Element* GetNamed(const etk::UString& _name);
			const Element* GetNamed(const etk::UString& _name) const;
			/**
			 * @brief Get the internal data of the element (if the element has some sub node thay are converted in xml string ==> like this it is not needed to use <![CDATA[...]]>
			 * @return the curent data string.
			 */
			etk::UString GetText(void);
		protected:
			bool SubParse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos, bool _mainNode=false);
		public: // herited function:
			virtual nodeType_te GetType(void) const { return typeElement; };
			virtual bool Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos);
			virtual bool Generate(etk::UString& _data, int32_t _indent) const;
			virtual exml::Element* ToElement(void) { return this; };
			virtual const exml::Element* ToElement(void) const { return this; };
			virtual void Clear(void);
	};
};


#endif


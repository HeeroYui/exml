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
#include <exml/AttributeList.h>

namespace exml {
	/**
	 * @brief Basic element Node of an XML document &lt;YYYYY&gt;
	 */
	class Element : public exml::AttributeList {
		protected:
			/**
			 * @brief Constructor
			 */
			Element() { };
			/**
			 * @brief Constructor
			 * @param[in] _value Element name;
			 */
			Element(const std::string& _value) :
			  exml::AttributeList(_value) {
				
			};
		public:
			/**
			 * @brief factory of an exml::Element
			 * @param[in] _value Name of the node.
			 * @return Shared pointer on the Element
			 */
			static ememory::SharedPtr<Element> create(const std::string& _value="");
		protected:
			std::vector<ememory::SharedPtr<exml::Node>> m_listSub; //!< List of subNodes
		public:
			/**
			 * @brief get the number of sub element in the node (can be exml::Comment ; exml::Element ; exml::Text :exml::Declaration).
			 * @return a number >=0.
			 */
			size_t size() const {
				return m_listSub.size();
			};
			/**
			 * @brief add a node at the element (not exml::Attribute (move in the attribute automaticly).
			 * @param[in] _node Pointer of the node to add.
			 */
			void append(const ememory::SharedPtr<exml::Node>& _node);
			/**
			 * @brief get the type of the element id.
			 * @param[in] _id Id of the element.
			 * @return the Current type of the element or exml::typeUnknow.
			 */
			enum nodeType getType(int32_t _id) const;
			/**
			 * @brief get the Node pointer of the element id.
			 * @param[in] _id Id of the element.
			 * @return Pointer on node.
			 */
			ememory::SharedPtr<Node> getNode(int32_t _id);
			/**
			 * @brief get the Node pointer of the element id.
			 * @param[in] _id Id of the element.
			 * @return Pointer on node.
			 */
			ememory::SharedPtr<const Node> getNode(int32_t _id) const;
			/**
			 * @brief get the element casted in Element (if the node is not an element return NULL).
			 * @param[in] _id Id of the element.
			 * @return Pointer on the element or NULL.
			 */
			ememory::SharedPtr<Element> getElement(int32_t _id);
			/**
			 * @brief get the element casted in Element (if the node is not an element return NULL).
			 * @param[in] _id Id of the element.
			 * @return Pointer on the element or NULL.
			 */
			ememory::SharedPtr<const Element> getElement(int32_t _id) const;
			/**
			 * @brief get an element with his name (work only with exml::Element)
			 * @param[in] _name Name of the element that is requested
			 * @return Pointer on the element or NULL.
			 */
			ememory::SharedPtr<Element> getNamed(const std::string& _name);
			/**
			 * @brief get an element with his name (work only with exml::Element)
			 * @param[in] _name Name of the element that is requested
			 * @return Pointer on the element or NULL.
			 */
			ememory::SharedPtr<const Element> getNamed(const std::string& _name) const;
			/**
			 * @brief get the internal data of the element (if the element has some sub node thay are converted in xml string  == > like this it is not needed to use <![CDATA[...]]>
			 * @return the curent data string. if Only one text node, then we get the parssed data (no &amp; ...) if more than one node, then we transform &,",',<,> in xml normal text...
			 */
			std::string getText() const;
		protected:
			/**
			 * @brief Parse sub node string
			 * @param[in] _data all file string data
			 * @param[in,out] _pos Position to start parsing in the file and return the end of parsing
			 * @param[in] _caseSensitive Case sensitive parsing (usefull for html)
			 * @param[in] _filePos Current File position of the parsing
			 * @param[in] _doc Document base reference
			 * @param[in] _mainNode if true, this is the first root node
			 * @return true parsing is done OK
			 * @return false An error appear in the parsing
			 */
			bool subParse(const std::string& _data,
			              int32_t& _pos,
			              bool _caseSensitive,
			              exml::FilePos& _filePos,
			              exml::Document& _doc,
			              bool _mainNode=false);
		public:
			enum nodeType getType() const override {
				return nodeType_element;
			}
			bool iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::FilePos& _filePos, exml::Document& _doc) override;
			bool iGenerate(std::string& _data, int32_t _indent) const override;
			ememory::SharedPtr<exml::Element> toElement() override {
				return std::static_pointer_cast<exml::Element>(shared_from_this());
			}
			ememory::SharedPtr<const exml::Element> toElement() const override {
				return std::static_pointer_cast<const exml::Element>(shared_from_this());
			}
			void clear() override;
	};
}


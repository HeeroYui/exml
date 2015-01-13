/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ETK_XML_ELEMENT_H__
#define __ETK_XML_ELEMENT_H__

#include <exml/Node.h>
#include <vector>
#include <exml/AttributeList.h>

namespace exml {
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
			static std::shared_ptr<Element> create();
			static std::shared_ptr<Element> create(const std::string& _value);
			/**
			 * @brief Destructor
			 */
			virtual ~Element();
		protected:
			std::vector<std::shared_ptr<exml::Node>> m_listSub;
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
			void append(const std::shared_ptr<exml::Node>& _node);
			/**
			 * @brief get the type of the element id.
			 * @param[in] _id Id of the element.
			 * @return the Current type of the element or exml::typeUnknow.
			 */
			enum nodeType getType(int32_t _id);
			const enum nodeType getType(int32_t _id) const;
			/**
			 * @brief get the Node pointer of the element id.
			 * @param[in] _id Id of the element.
			 * @return Pointer on node.
			 */
			std::shared_ptr<Node> getNode(int32_t _id);
			std::shared_ptr<const Node> getNode(int32_t _id) const;
			/**
			 * @brief get the element casted in Element (if the node is not an element return NULL).
			 * @param[in] _id Id of the element.
			 * @return Pointer on the element or NULL.
			 */
			std::shared_ptr<Element> getElement(int32_t _id);
			std::shared_ptr<const Element> getElement(int32_t _id) const;
			/**
			 * @brief get an element with his name (work only with exml::Element)
			 * @param[in] _name Name of the element that is requested
			 * @return Pointer on the element or NULL.
			 */
			std::shared_ptr<Element> getNamed(const std::string& _name);
			std::shared_ptr<const Element> getNamed(const std::string& _name) const;
			/**
			 * @brief get the internal data of the element (if the element has some sub node thay are converted in xml string  == > like this it is not needed to use <![CDATA[...]]>
			 * @return the curent data string. if Only one text node, then we get the parssed data (no &amp; ...) if more than one node, then we transform &,",',<,> in xml normal text...
			 */
			std::string getText();
		protected:
			bool subParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc, bool _mainNode=false);
		public: // herited function:
			virtual enum nodeType getType() const {
				return typeElement;
			};
			virtual bool iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc);
			virtual bool iGenerate(std::string& _data, int32_t _indent) const;
			virtual std::shared_ptr<exml::Element> toElement() {
				return std::static_pointer_cast<exml::Element>(shared_from_this());
			};
			virtual std::shared_ptr<const exml::Element> toElement() const {
				return std::static_pointer_cast<const exml::Element>(shared_from_this());
			};
			virtual void clear();
	};
};


#endif


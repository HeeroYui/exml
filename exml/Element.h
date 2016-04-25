/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <exml/Node.h>
#include <vector>
#include <exml/AttributeList.h>
#include <exml/iterator.h>

namespace exml {
	
	/**
	 * @brief Basic element Node of an XML document &lt;YYYYY&gt;
	 * @todo Remove node with a specisic ID/Iterator (erase)
	 * @todo Remove an Node with his exml::Element link
	 */
	class ElementData {
		private:
			exml::Element* m_data; //!< Pointer on the exml::Element class (must not be nullptr)
		public:
			/**
			 * @brief constructor on the ElementData class
			 * @param[in] _list Get pointer on the exml::Element class (must not be nullptr)
			 */
			ElementData(exml::Element* _list);
		public:
			/**
			 * @brief get the number of sub element in the node (can be exml::Comment ; exml::Element ; exml::Text :exml::Declaration).
			 * @return a number >=0.
			 */
			size_t size() const;
			/**
			 * @brief add a node at the element (not exml::Attribute (move in the attribute automaticly).
			 * @param[in] _node Node to add.
			 */
			void add(const exml::Node& _node);
			/**
			 * @brief Remove a node with his name.
			 * @param[in] _nodeName Name of the node.
			 */
			void remove(const std::string& _nodeName);
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
			exml::Node operator[] (int32_t _id);
			/**
			 * @brief get the Node pointer of the element id.
			 * @param[in] _id Id of the element.
			 * @return Pointer on node.
			 */
			const exml::Node operator[] (int32_t _id) const;
			/**
			 * @brief get an element with his name (work only with exml::Element)
			 * @param[in] _name Name of the element that is requested
			 * @return Pointer on the element or NULL.
			 */
			exml::Element operator[] (const std::string& _name);
			/**
			 * @brief get an element with his name (work only with exml::Element)
			 * @param[in] _name Name of the element that is requested
			 * @return Pointer on the element or NULL.
			 */
			const exml::Element operator[] (const std::string& _name) const;
		public:
			using iterator = exml::iterator<exml::ElementData, exml::Node>; //!< Specify iterator of the element methode
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
	 * @brief Basic element Node of an XML document &lt;YYYYY&gt;
	 */
	class Element : public exml::AttributeList {
		public:
			ElementData nodes; //!< All Sub-nodes interface
		public:
			/**
			 * @brief Constructor
			 * @param[in] _internalNode Internal Node to set data
			 */
			Element(ememory::SharedPtr<exml::internal::Node> _internalNode);
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 */
			Element(const exml::Element& _obj);
			/**
			 * @brief Constructor
			 * @param[in] _value Element name;
			 */
			Element(const std::string& _value="");
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 * @return Local reference on this class
			 */
			exml::Element& operator= (const exml::Element& _obj);
			/**
			 * @brief get the internal data of the element (if the element has some sub node thay are converted in xml string  == > like this it is not needed to use <![CDATA[...]]>
			 * @return the curent data string. if Only one text node, then we get the parssed data (no &amp; ...) if more than one node, then we transform &,",',<,> in xml normal text...
			 */
			std::string getText() const;
		public:
			void clear() override;
	};
}


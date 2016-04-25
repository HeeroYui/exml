/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <ememory/memory.h>
#include <etk/types.h>
#include <etk/math/Vector2D.h>
#include <exml/FilePos.h>
#include <exml/internal/Node.h>
#include <exml/nodeType.h>

/**
 * @brief exml namespace containing all function for XML interpretor
 */
namespace exml {
	class Document;
	class Attribute;
	class Comment;
	class Declaration;
	class Element;
	class Text;
	class AttributeListData;
	class ElementData;
	/**
	 * @brief Basic main object of all xml elements.
	 */
	class Node {
		friend class exml::Element;
		friend class exml::AttributeListData;
		friend class exml::ElementData;
		protected:
			ememory::SharedPtr<exml::internal::Node> m_data; //!< internal reference on a node
		public:
			/**
			 * @brief basic element of a xml structure
			 * @param[in] _internalNode Internal reference of the Node
			 */
			Node(ememory::SharedPtr<exml::internal::Node> _internalNode);
			/**
			 * @brief basic element of a xml structure
			 */
			Node();
		public:
			/**
			 * @brief Virtualize destructor
			 */
			virtual ~Node() = default;
		public:
			/**
			 * @brief Check if the element exit
			 * @return true The element exist
			 * @return false The element does NOT exist
			 */
			bool exist() const;
			/**
			 * @brief get the current position where the element is in the file
			 * @return The file position reference
			 */
			exml::FilePos getPos() const;
			/**
			 * @brief set the value of the node.
			 * @param[in] _value New value of the node.
			 */
			virtual void setValue(std::string _value);
			/**
			 * @brief get the current element Value.
			 * @return the reference of the string value.
			 */
			const std::string& getValue() const;
			/**
			 * @brief get the node type.
			 * @return the type of the Node.
			 */
			enum nodeType getType() const;
			/**
			 * @brief Cast the element in a Document if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			exml::Document toDocument();
			/**
			 * @brief Cast the element in a Document if it is possible.
			 * @return CONST pointer on the class or nullptr.
			 */
			const exml::Document toDocument() const;
			/**
			 * @brief Cast the element in a Attribute if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			exml::Attribute toAttribute();
			/**
			 * @brief Cast the element in a Attribute if it is possible.
			 * @return CONST pointer on the class or nullptr.
			 */
			const exml::Attribute toAttribute() const;
			/**
			 * @brief Cast the element in a Comment if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			exml::Comment toComment();
			/**
			 * @brief Cast the element in a Comment if it is possible.
			 * @return CONST pointer on the class or nullptr.
			 */
			const exml::Comment toComment() const;
			/**
			 * @brief Cast the element in a Declaration if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			exml::Declaration toDeclaration();
			/**
			 * @brief Cast the element in a Declaration if it is possible.
			 * @return CONST pointer on the class or nullptr.
			 */
			const exml::Declaration toDeclaration() const;
			/**
			 * @brief Cast the element in a Element if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			exml::Element toElement();
			/**
			 * @brief Cast the element in a Element if it is possible.
			 * @return CONST pointer on the class or nullptr.
			 */
			const exml::Element toElement() const;
			/**
			 * @brief Cast the element in a Text if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			exml::Text toText();
			/**
			 * @brief Cast the element in a Text if it is possible.
			 * @return CONST pointer on the class or nullptr.
			 */
			const exml::Text toText() const;
			/**
			 * @brief check if the node is a exml::Document
			 * @return true if the node is a exml::Document
			 */
			bool isDocument() const;
			/**
			 * @brief check if the node is a exml::Attribute
			 * @return true if the node is a exml::Attribute
			 */
			bool isAttribute() const;
			/**
			 * @brief check if the node is a exml::Comment
			 * @return true if the node is a exml::Comment
			 */
			bool isComment() const;
			/**
			 * @brief check if the node is a exml::Declaration
			 * @return true if the node is a exml::Declaration
			 */
			bool isDeclaration() const;
			/**
			 * @brief check if the node is a exml::Element
			 * @return true if the node is a exml::Element
			 */
			bool isElement() const;
			/**
			 * @brief check if the node is a exml::Text
			 * @return true if the node is a exml::Text
			 */
			bool isText() const;
			/**
			 * @brief clear the Node
			 */
			virtual void clear();
	};
	//! @not_in_doc
	std::ostream& operator <<(std::ostream& _os, const exml::Node& _obj);
}

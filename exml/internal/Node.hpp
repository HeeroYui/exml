/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <ememory/memory.hpp>
#include <etk/types.hpp>
#include <etk/math/Vector2D.hpp>
#include <exml/FilePos.hpp>
#include <exml/nodeType.hpp>

/**
 * @brief exml namespace containing all function for XML interpretor
 */
namespace exml {
	namespace internal {
		//#define ENABLE_DISPLAY_PARSED_ELEMENT
		//#define ENABLE_CRITICAL_WHEN_ERROR
		#if 1
			//! manual debug element (when developpe exml)
			#define EXML_PARSE_ELEMENT EXML_VERBOSE
		#else
			#define EXML_PARSE_ELEMENT EXML_DEBUG
		#endif
		#if 1
			//! manual debug element (when developpe exml)
			#define EXML_PARSE_ATTRIBUTE EXML_VERBOSE
		#else
			#define EXML_PARSE_ATTRIBUTE EXML_DEBUG
		#endif
		class Document;
		class Attribute;
		class Comment;
		class Declaration;
		class Element;
		class Text;
		
		/**
		 * @brief Basic main object of all xml elements.
		 */
		class Node : public ememory::EnableSharedFromThis<Node>{
			protected:
				/**
				 * @brief basic element of a xml structure
				 */
				Node() :
				  m_pos(0,0) {
					
				};
				/**
				 * @brief basic element of a xml structure
				 * @param[in] _value value of the node
				 */
				Node(const etk::String& _value);
			public:
				/**
				 * @brief Virtualize destructor
				 */
				virtual ~Node() = default;
			public:
				/**
				 * @brief parse the Current node [pure VIRUAL]
				 * @param[in] _data data string to parse.
				 * @param[in,out] _pos position in the string to start parse, return the position end of parsing.
				 * @param[in] _caseSensitive Request a parsion of element that is not case sensitive (all element is in low case)
				 * @param[in,out] _filePos file parsing position (line x col x)
				 * @param[in,out] _doc Base document reference
				 * @return false if an error occured.
				 */
				virtual bool iParse(const etk::String& _data, int32_t& _pos, bool _caseSensitive, exml::FilePos& _filePos, exml::internal::Document& _doc) = 0;
				/**
				 * @brief generate a string with the tree of the xml
				 * @param[in,out] _data string where to add the elements
				 * @param[in] _indent current indentation of the file
				 * @return false if an error occured.
				 */
				virtual bool iGenerate(etk::String& _data, int32_t _indent) const;
			protected:
				exml::FilePos m_pos; //!< position in the readed file  == > not correct when the file is generated
			public:
				/**
				 * @brief get the current position where the element is in the file
				 * @return The file position reference
				 */
				const exml::FilePos& getPos() const;
			protected:
				etk::String m_value; //!< value of the node (for element this is the name, for text it is the inside text ...)
			public:
				/**
				 * @brief set the value of the node.
				 * @param[in] _value New value of the node.
				 */
				virtual void setValue(etk::String _value);
				/**
				 * @brief get the current element Value.
				 * @return the reference of the string value.
				 */
				virtual const etk::String& getValue() const;
			public:
				/**
				 * @brief get the node type.
				 * @return the type of the Node.
				 */
				virtual enum nodeType getType() const;
			protected:
				/**
				 * @brief add indentation of the string input.
				 * @param[in,out] _data String where the indentation is done.
				 * @param[in] _indent Number of tab to add at the string.
				 */
				void addIndent(etk::String& _data, int32_t _indent) const;
				/**
				 * @brief Display the cuurent element that is curently parse.
				 * @param[in] _val Char that is parsed.
				 * @param[in] _filePos Position of the char in the file.
				 */
				void drawElementParsed(char32_t _val, const exml::FilePos& _filePos) const;
				/**
				 * @brief check if an element or attribute is availlable (not : !"#$%&'()*+,/;<=>?@[\]^`{|}~ \\n\\t\\r and for first char : not -.0123456789).
				 * @param[in] _val Value to check the conformity.
				 * @param[in] _firstChar True if the element check is the first char.
				 * @return true The value can be a part of attribute name
				 * @return false The value can NOT be a part of attribute name
				 */
				bool checkAvaillable(char32_t _val, bool _firstChar) const;
				/**
				 * @brief count the number of white char in the string from the specify position (stop at the first element that is not a white char)
				 * @param[in] _data Data to parse.
				 * @param[in] _pos Start position in the string.
				 * @param[out] _filePos new poistion of te file to add.
				 * @return number of white element.
				 */
				int32_t countWhiteChar(const etk::String& _data, int32_t _pos, exml::FilePos& _filePos) const;
			public:
				/**
				 * @brief Cast the element in a Document if it is possible.
				 * @return pointer on the class or null.
				 */
				virtual ememory::SharedPtr<exml::internal::Document> toDocument();
				/**
				 * @brief Cast the element in a Document if it is possible.
				 * @return CONST pointer on the class or null.
				 */
				virtual const ememory::SharedPtr<exml::internal::Document> toDocument() const;
				/**
				 * @brief Cast the element in a Attribute if it is possible.
				 * @return pointer on the class or null.
				 */
				virtual ememory::SharedPtr<exml::internal::Attribute> toAttribute();
				/**
				 * @brief Cast the element in a Attribute if it is possible.
				 * @return CONST pointer on the class or null.
				 */
				virtual const ememory::SharedPtr<exml::internal::Attribute> toAttribute() const;
				/**
				 * @brief Cast the element in a Comment if it is possible.
				 * @return pointer on the class or null.
				 */
				virtual ememory::SharedPtr<exml::internal::Comment> toComment();
				/**
				 * @brief Cast the element in a Comment if it is possible.
				 * @return CONST pointer on the class or null.
				 */
				virtual const ememory::SharedPtr<exml::internal::Comment> toComment() const;
				/**
				 * @brief Cast the element in a Declaration if it is possible.
				 * @return pointer on the class or null.
				 */
				virtual ememory::SharedPtr<exml::internal::Declaration> toDeclaration();
				/**
				 * @brief Cast the element in a Declaration if it is possible.
				 * @return CONST pointer on the class or null.
				 */
				virtual const ememory::SharedPtr<exml::internal::Declaration> toDeclaration() const;
				/**
				 * @brief Cast the element in a Element if it is possible.
				 * @return pointer on the class or null.
				 */
				virtual ememory::SharedPtr<exml::internal::Element> toElement();
				/**
				 * @brief Cast the element in a Element if it is possible.
				 * @return CONST pointer on the class or null.
				 */
				virtual const ememory::SharedPtr<exml::internal::Element> toElement() const;
				/**
				 * @brief Cast the element in a Text if it is possible.
				 * @return pointer on the class or null.
				 */
				virtual ememory::SharedPtr<exml::internal::Text> toText();
				/**
				 * @brief Cast the element in a Text if it is possible.
				 * @return CONST pointer on the class or null.
				 */
				virtual const ememory::SharedPtr<exml::internal::Text> toText() const;
				
				/**
				 * @brief check if the node is a exml::internal::Document
				 * @return true if the node is a exml::internal::Document
				 */
				bool isDocument() const;
				/**
				 * @brief check if the node is a exml::internal::Attribute
				 * @return true if the node is a exml::internal::Attribute
				 */
				bool isAttribute() const;
				/**
				 * @brief check if the node is a exml::internal::Comment
				 * @return true if the node is a exml::internal::Comment
				 */
				bool isComment() const;
				/**
				 * @brief check if the node is a exml::internal::Declaration
				 * @return true if the node is a exml::internal::Declaration
				 */
				bool isDeclaration() const;
				/**
				 * @brief check if the node is a exml::internal::Element
				 * @return true if the node is a exml::internal::Element
				 */
				bool isElement() const;
				/**
				 * @brief check if the node is a exml::internal::Text
				 * @return true if the node is a exml::internal::Text
				 */
				bool isText() const;
				
				/**
				 * @brief clear the Node
				 */
				virtual void clear();
		};
	}
}

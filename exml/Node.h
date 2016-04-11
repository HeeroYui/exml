/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <ememory/memory.h>
#include <etk/types.h>
#include <etk/math/Vector2D.h>
#include <exml/FilePos.h>

/**
 * @brief exml namespace containing all function for XML interpretor
 */
namespace exml {
	//#define ENABLE_DISPLAY_PARSED_ELEMENT
	//#define ENABLE_CRITICAL_WHEN_ERROR
	#if 1
		#define EXML_PARSE_ELEMENT EXML_VERBOSE
	#else
		#define EXML_PARSE_ELEMENT EXML_DEBUG
	#endif
	#if 1
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
	
	enum nodeType {
		typeUnknow, //!< might be an error ...
		typeNode, //!< might be an error ...
		typeDocument, //!< all the file main access
		typeDeclaration, //!< <?xml ... ?>
		typeAttribute, //!< the <Element ATTRIBUTE="ATTRIBUTE_VALUE" />
		typeElement,  //!< the <XXX> ... </XXX>
		typeComment, //!< comment node : <!--   -->
		typeText, //!< <XXX> InsideText </XXX>
	};
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
			 * @param[in] value of the node
			 */
			Node(const std::string& _value);
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
			 * @param[in,out] file parsing position (line x col x)
			 * @return false if an error occured.
			 */
			virtual bool iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::FilePos& _filePos, exml::Document& _doc) = 0;
			/**
			 * @brief generate a string with the tree of the xml
			 * @param[in,out] _data string where to add the elements
			 * @param[in] current indentation of the file
			 * @return false if an error occured.
			 */
			virtual bool iGenerate(std::string& _data, int32_t _indent) const;
		protected:
			exml::FilePos m_pos; //!< position in the readed file  == > not correct when the file is generated
		public:
			/**
			 * @brief get the current position where the element is in the file
			 */
			const exml::FilePos& getPos() const;
		protected:
			std::string m_value; //!< value of the node (for element this is the name, for text it is the inside text ...)
		public:
			/**
			 * @brief set the value of the node.
			 * @param[in] _value New value of the node.
			 */
			virtual void setValue(std::string _value);
			/**
			 * @brief get the current element Value.
			 * @return the reference of the string value.
			 */
			virtual const std::string& getValue() const;
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
			void addIndent(std::string& _data, int32_t _indent) const;
			/**
			 * @brief Display the cuurent element that is curently parse.
			 * @param[in] _val Char that is parsed.
			 * @param[in] _filePos Position of the char in the file.
			 */
			void drawElementParsed(char32_t _val, const exml::FilePos& _filePos) const;
			/**
			 * @brief check if an element or attribute is availlable (not : !"#$%&'()*+,/;<=>?@[\]^`{|}~ \n\t\r and for first char : not -.0123456789).
			 * @param[in] _val Value to check the conformity.
			 * @param[in] _firstChar True if the element check is the first char.
			 */
			bool checkAvaillable(char32_t _val, bool _firstChar) const;
			/**
			 * @brief count the number of white char in the string from the specify position (stop at the first element that is not a white char)
			 * @param[in] _data Data to parse.
			 * @param[in] _pos Start position in the string.
			 * @param[out] _filePos new poistion of te file to add.
			 * @return number of white element.
			 */
			int32_t countWhiteChar(const std::string& _data, int32_t _pos, exml::FilePos& _filePos) const;
		public:
			/**
			 * @brief Cast the element in a Document if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			virtual ememory::SharedPtr<exml::Document> toDocument();
			/**
			 * @brief Cast the element in a Document if it is possible.
			 * @return CONST pointer on the class or nullptr.
			 */
			virtual ememory::SharedPtr<const exml::Document> toDocument() const;
			/**
			 * @brief Cast the element in a Attribute if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			virtual ememory::SharedPtr<exml::Attribute> toAttribute();
			/**
			 * @brief Cast the element in a Attribute if it is possible.
			 * @return CONST pointer on the class or nullptr.
			 */
			virtual ememory::SharedPtr<const exml::Attribute> toAttribute() const;
			/**
			 * @brief Cast the element in a Comment if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			virtual ememory::SharedPtr<exml::Comment> toComment();
			/**
			 * @brief Cast the element in a Comment if it is possible.
			 * @return CONST pointer on the class or nullptr.
			 */
			virtual ememory::SharedPtr<const exml::Comment> toComment() const;
			/**
			 * @brief Cast the element in a Declaration if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			virtual ememory::SharedPtr<exml::Declaration> toDeclaration();
			/**
			 * @brief Cast the element in a Declaration if it is possible.
			 * @return CONST pointer on the class or nullptr.
			 */
			virtual ememory::SharedPtr<const exml::Declaration> toDeclaration() const;
			/**
			 * @brief Cast the element in a Element if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			virtual ememory::SharedPtr<exml::Element> toElement();
			/**
			 * @brief Cast the element in a Element if it is possible.
			 * @return CONST pointer on the class or nullptr.
			 */
			virtual ememory::SharedPtr<const exml::Element> toElement() const;
			/**
			 * @brief Cast the element in a Text if it is possible.
			 * @return pointer on the class or nullptr.
			 */
			virtual ememory::SharedPtr<exml::Text> toText();
			/**
			 * @brief Cast the element in a Text if it is possible.
			 * @return CONST pointer on the class or nullptr.
			 */
			virtual ememory::SharedPtr<const exml::Text> toText() const;
			
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
}

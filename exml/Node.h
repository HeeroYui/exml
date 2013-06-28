/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_XML_NODE_H__
#define __ETK_XML_NODE_H__

#include <etk/types.h>
#include <etk/UString.h>
#include <etk/math/Vector2D.h>

namespace exml
{
	//#define ENABLE_DISPLAY_PARSED_ELEMENT
	class Document;
	class Attribute;
	class Comment;
	class Declaration;
	class Element;
	class Text;
	
	typedef enum {
		typeUnknow, //!< might be an error ...
		typeNode, //!< might be an error ...
		typeDocument, //!< all the file main access
		typeDeclaration, //!< <?xml ... ?>
		typeAttribute, //!< the <Element ATTRIBUTE="ATTRIBUTE_VALUE" />
		typeElement,  //!< the <XXX> ... </XXX>
		typeComment, //!< comment node : <!--   -->
		typeText, //!< <XXX> InsideText </XXX>
	} nodeType_te;
	
	class Node
	{
		public:
			/**
			 * @brief basic element of a xml structure
			 */
			Node(void) : m_pos(0,0) { };
			/**
			 * @brief basic element of a xml structure
			 * @param[in] value of the node
			 */
			Node(const etk::UString& _value);
			/**
			 * @brief destructor
			 */
			virtual ~Node(void) { };
		public:
			/**
			 * @brief Parse the Current node [pure VIRUAL]
			 * @param[in] _data data string to parse.
			 * @param[in,out] _pos position in the string to start parse, return the position end of parsing.
			 * @param[in] _caseSensitive Request a parsion of element that is not case sensitive (all element is in low case)
			 * @param[in,out] file parsing position (line x col x)
			 * @return false if an error occured.
			 */
			virtual bool Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos) = 0;
			/**
			 * @brief Generate a string with the tree of the xml
			 * @param[in,out] _data string where to add the elements
			 * @param[in] current indentation of the file
			 * @return false if an error occured.
			 */
			virtual bool Generate(etk::UString& _data, int32_t _indent) const { return true; };
		protected:
			ivec2 m_pos; //!< position in the readed file ==> not correct when the file is generated
		public:
			/**
			 * @brief Get the current position where the element is in the file
			 */
			const ivec2& GetPos(void) { return m_pos; };
		protected:
			etk::UString m_value; //!< value of the node (for element this is the name, for text it is the inside text ...)
		public:
			/**
			 * @brief Set the value of the node.
			 * @param[in] _value New value of the node.
			 */
			virtual void SetValue(etk::UString _value) { m_value = _value; };
			/**
			 * @brief Get the current element Value.
			 * @return the reference of the string value.
			 */
			virtual const etk::UString& GetValue(void) const { return m_value; };
		public:
			/**
			 * @brief Get the node type.
			 * @return the type of the Node.
			 */
			virtual nodeType_te GetType(void) const { return typeNode; };
		protected:
			/**
			 * @brief Add indentation of the string input.
			 * @param[in,out] _data String where the indentation is done.
			 * @param[in] _indent Number of tab to add at the string.
			 */
			void AddIndent(etk::UString& _data, int32_t _indent) const;
			/**
			 * @brief Display the cuurent element that is curently parse.
			 * @param[in] _val Char that is parsed.
			 * @param[in] _filePos Position of the char in the file.
			 */
			void DrawElementParsed(const etk::UniChar& _val, const ivec2& _filePos) const;
			/**
			 * @brief check if an element or attribute is availlable (not : !"#$%&'()*+,/;<=>?@[\]^`{|}~ \n\t\r and for first char : not -.0123456789).
			 * @param[in] _val Value to check the conformity.
			 * @param[in] _firstChar True if the element check is the first char.
			 */
			bool CheckAvaillable(const etk::UniChar& _val, bool _firstChar) const;
			/**
			 * @brief count the number of white char in the string from the specify position (stop at the first element that is not a white char)
			 * @param[in] _data Data to parse.
			 * @param[in] _pos Start position in the string.
			 * @return number of white element.
			 */
			int32_t CountWhiteChar(const etk::UString& _data, int32_t _pos) const;
		public:
			/**
			 * @brief Cast the element in a Document if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual exml::Document* ToDocument(void) { return NULL; };
			virtual const exml::Document* ToDocument(void) const { return NULL; };
			/**
			 * @brief Cast the element in a Attribute if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual exml::Attribute* ToAttribute(void) { return NULL; };
			virtual const exml::Attribute* ToAttribute(void) const { return NULL; };
			/**
			 * @brief Cast the element in a Comment if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual exml::Comment* ToComment(void) { return NULL; };
			virtual const exml::Comment* ToComment(void) const { return NULL; };
			/**
			 * @brief Cast the element in a Declaration if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual exml::Declaration* ToDeclaration(void) { return NULL; };
			virtual const exml::Declaration* ToDeclaration(void) const { return NULL; };
			/**
			 * @brief Cast the element in a Element if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual exml::Element* ToElement(void) { return NULL; };
			virtual const exml::Element* ToElement(void) const { return NULL; };
			/**
			 * @brief Cast the element in a Text if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual exml::Text* ToText(void) { return NULL; };
			virtual const exml::Text* ToText(void) const{ return NULL; };
			
			/**
			 * @brief Check if the node is a exml::Document
			 * @return true if the node is a exml::Document
			 */
			bool IsDocument(void) const { return GetType()==exml::typeDocument; };
			/**
			 * @brief Check if the node is a exml::Attribute
			 * @return true if the node is a exml::Attribute
			 */
			bool IsAttribute(void) const { return GetType()==exml::typeAttribute; };
			/**
			 * @brief Check if the node is a exml::Comment
			 * @return true if the node is a exml::Comment
			 */
			bool IsComment(void) const { return GetType()==exml::typeComment; };
			/**
			 * @brief Check if the node is a exml::Declaration
			 * @return true if the node is a exml::Declaration
			 */
			bool IsDeclaration(void) const { return GetType()==exml::typeDeclaration; };
			/**
			 * @brief Check if the node is a exml::Element
			 * @return true if the node is a exml::Element
			 */
			bool IsElement(void) const { return GetType()==exml::typeElement; };
			/**
			 * @brief Check if the node is a exml::Text
			 * @return true if the node is a exml::Text
			 */
			bool IsText(void) const { return GetType()==exml::typeText; };
			
			/**
			 * @brief Clear the Node
			 */
			virtual void Clear(void);
	};
};

#endif


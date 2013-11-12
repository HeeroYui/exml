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
	
	class filePos {
		private:
			int32_t m_col;
			int32_t m_line;
		public:
			filePos(void) :
			  m_col(0),
			  m_line(0) {
				
			};
			filePos(int32_t _line, int32_t _col) :
			  m_col(_col),
			  m_line(_line) {
				
			};
			~filePos(void) { };
			filePos& operator ++(void) {
				m_col++;
				return *this;
			};
			filePos& operator --(void) {
				m_col--;
				if(m_col<0) {
					m_col=0;
				}
				return *this;
			};
			const filePos& operator +=(const filePos& _obj) {
				if (_obj.m_line == 0) {
					m_col += _obj.m_col;
				} else {
					m_col = _obj.m_col;
					m_line += _obj.m_line;
				}
				return *this;
			};
			const filePos& operator +=(int32_t _col) {
				m_col += _col;
				return *this;
			};
			const filePos& operator= (const filePos& _obj ) {
				m_col = _obj.m_col;
				m_line = _obj.m_line;
				return *this;
			}
			void newLine(void) {
				m_col=0;
				m_line++;
			};
			bool check(char32_t _val) {
				m_col++;
				if (_val == '\n') {
					newLine();
					return true;
				}
				return false;
			}
			void set(int32_t _line, int32_t _col) {
				m_col = _col;
				m_line = _line;
			}
			void clear(void) {
				m_col = 0;
				m_line = 0;
			}
			int32_t getCol(void) const {
				return m_col;
			};
			int32_t getLine(void) const {
				return m_line;
			};
	};
	etk::CCout& operator <<(etk::CCout& _os, const filePos& _obj);
	
	class Node {
		public:
			/**
			 * @brief basic element of a xml structure
			 */
			Node(void) :
			  m_pos(0,0) {
				
			};
			/**
			 * @brief basic element of a xml structure
			 * @param[in] value of the node
			 */
			Node(const std::string& _value);
			Node(const std::u32string& _value);
			/**
			 * @brief destructor
			 */
			virtual ~Node(void) { };
		public:
			/**
			 * @brief parse the Current node [pure VIRUAL]
			 * @param[in] _data data string to parse.
			 * @param[in,out] _pos position in the string to start parse, return the position end of parsing.
			 * @param[in] _caseSensitive Request a parsion of element that is not case sensitive (all element is in low case)
			 * @param[in,out] file parsing position (line x col x)
			 * @return false if an error occured.
			 */
			virtual bool iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc) = 0;
			/**
			 * @brief generate a string with the tree of the xml
			 * @param[in,out] _data string where to add the elements
			 * @param[in] current indentation of the file
			 * @return false if an error occured.
			 */
			virtual bool iGenerate(std::string& _data, int32_t _indent) const {
				return true;
			};
		protected:
			exml::filePos m_pos; //!< position in the readed file  == > not correct when the file is generated
		public:
			/**
			 * @brief get the current position where the element is in the file
			 */
			const exml::filePos& getPos(void) {
				return m_pos;
			};
		protected:
			std::string m_value; //!< value of the node (for element this is the name, for text it is the inside text ...)
		public:
			/**
			 * @brief set the value of the node.
			 * @param[in] _value New value of the node.
			 */
			virtual void setValue(std::string _value) {
				m_value = _value;
			};
			virtual void setValue(std::u32string _value);
			/**
			 * @brief get the current element Value.
			 * @return the reference of the string value.
			 */
			virtual const std::string& getValue(void) const {
				return m_value;
			};
			virtual std::u32string getUValue(void) const;
		public:
			/**
			 * @brief get the node type.
			 * @return the type of the Node.
			 */
			virtual enum nodeType getType(void) const {
				return typeNode;
			};
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
			void drawElementParsed(char32_t _val, const exml::filePos& _filePos) const;
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
			int32_t countWhiteChar(const std::string& _data, int32_t _pos, exml::filePos& _filePos) const;
		public:
			/**
			 * @brief Cast the element in a Document if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual exml::Document* toDocument(void) {
				return NULL;
			};
			virtual const exml::Document* toDocument(void) const {
				return NULL;
			};
			/**
			 * @brief Cast the element in a Attribute if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual exml::Attribute* toAttribute(void) {
				return NULL;
			};
			virtual const exml::Attribute* toAttribute(void) const {
				return NULL;
			};
			/**
			 * @brief Cast the element in a Comment if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual exml::Comment* toComment(void) {
				return NULL;
			};
			virtual const exml::Comment* toComment(void) const {
				return NULL;
			};
			/**
			 * @brief Cast the element in a Declaration if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual exml::Declaration* toDeclaration(void) {
				return NULL;
			};
			virtual const exml::Declaration* toDeclaration(void) const {
				return NULL;
			};
			/**
			 * @brief Cast the element in a Element if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual exml::Element* toElement(void) {
				return NULL;
			};
			virtual const exml::Element* toElement(void) const {
				return NULL;
			};
			/**
			 * @brief Cast the element in a Text if it is possible.
			 * @return pointer on the class or NULL.
			 */
			virtual exml::Text* toText(void) {
				return NULL;
			};
			virtual const exml::Text* toText(void) const{
				return NULL;
			};
			
			/**
			 * @brief check if the node is a exml::Document
			 * @return true if the node is a exml::Document
			 */
			bool isDocument(void) const {
				return getType() == exml::typeDocument;
			};
			/**
			 * @brief check if the node is a exml::Attribute
			 * @return true if the node is a exml::Attribute
			 */
			bool isAttribute(void) const {
				return getType() == exml::typeAttribute;
			};
			/**
			 * @brief check if the node is a exml::Comment
			 * @return true if the node is a exml::Comment
			 */
			bool isComment(void) const {
				return getType() == exml::typeComment;
			};
			/**
			 * @brief check if the node is a exml::Declaration
			 * @return true if the node is a exml::Declaration
			 */
			bool isDeclaration(void) const {
				return getType() == exml::typeDeclaration;
			};
			/**
			 * @brief check if the node is a exml::Element
			 * @return true if the node is a exml::Element
			 */
			bool isElement(void) const {
				return getType() == exml::typeElement;
			};
			/**
			 * @brief check if the node is a exml::Text
			 * @return true if the node is a exml::Text
			 */
			bool isText(void) const {
				return getType() == exml::typeText;
			};
			
			/**
			 * @brief clear the Node
			 */
			virtual void clear(void);
	};
};

#endif


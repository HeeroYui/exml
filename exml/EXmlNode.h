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
	class EXmlDocument;
	class EXmlAttribute;
	class EXmlComment;
	class EXmlDeclaration;
	class EXmlElement;
	class EXmlText;
	
	typedef enum {
		typeNode, //!< might be an error ...
		typeDocument, //!< all the file main access
		typeDeclaration, //!< <?xml ... ?>
		typeAttribute, //!< the <Element ATTRIBUTE="ATTRIBUTE_VALUE" />
		typeElement,  //!< the <XXX> ... </XXX>
		typeComment, //!< comment node : <!--   -->
		typeText, //!< <XXX> InsideText </XXX>
	} nodeType_te;
	
	class EXmlNode
	{
		public:
			EXmlNode(void) { };
			EXmlNode(const etk::UString& _value);
			virtual ~EXmlNode(void) { };
		protected:
			void AddIndent(etk::UString& _data, int32_t _indent);
		public:
			/**
			 * Parse the sub nodes and current nodes ...
			 */
			virtual bool Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos) = 0;
			virtual bool Generate(etk::UString& _data, int32_t _indent) { return true; };
		protected:
			etk::UString m_value;
		public:
			virtual void SetValue(etk::UString _value) { m_value = _value; };
			virtual const etk::UString& GetValue(void) { return m_value; };
		public:
			virtual nodeType_te GetType(void) { return typeNode; };
		protected:
			void DrawElementParsed(const etk::UniChar& _val, const ivec2& _firstChar);
			bool CheckAvaillable(const etk::UniChar& _val, bool _firstChar);
			int32_t CountWhiteChar(const etk::UString& _data, int32_t _pos);
		public:
			exml::EXmlDocument* ToDocument(void);
			exml::EXmlAttribute* ToAttribute(void);
			exml::EXmlComment* ToComment(void);
			exml::EXmlDeclaration* ToDeclaration(void);
			exml::EXmlElement* ToElement(void);
			exml::EXmlText* ToText(void);
			
			bool IsDocument(void) { return GetType()==exml::typeDocument; };
			bool IsAttribute(void) { return GetType()==exml::typeAttribute; };
			bool IsComment(void) { return GetType()==exml::typeComment; };
			bool IsDeclaration(void) { return GetType()==exml::typeDeclaration; };
			bool IsElement(void) { return GetType()==exml::typeElement; };
			bool IsText(void) { return GetType()==exml::typeText; };
	};
};

#endif


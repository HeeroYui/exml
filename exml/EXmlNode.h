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
			virtual ~EXmlNode(void) { };
		public:
			/**
			 * Parse the sub nodes and current nodes ...
			 */
			virtual bool Parse(const etk::UString& _data, int32_t _pos, bool _caseSensitive, ivec2& _filePos, int32_t& findLen) = 0;
		protected:
			etk::UString m_name;
		public:
			virtual void SetName(etk::UString _name) { m_name = _name; };
			virtual const etk::UString& GetName(void) { return m_name; };
		protected:
			etk::UString m_value;
		public:
			virtual void SetValue(etk::UString _value) { m_value = _value; };
			virtual const etk::UString& GetValue(void) { return m_value; };
		public:
			virtual nodeType_te GetType(void) { return typeNode; };
	};
};

#endif


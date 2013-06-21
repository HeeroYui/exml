/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_XML_ATTRIBUTE_H__
#define __ETK_XML_ATTRIBUTE_H__

#include <exml/EXmlNode.h>
#include <etk/Vector.h>

namespace exml
{
	class EXmlAttribute : public EXmlNode
	{
		public:
			EXmlAttribute(void) { };
			EXmlAttribute(const etk::UString& _name, const etk::UString& _value);
			virtual ~EXmlAttribute(void) { };
			virtual nodeType_te GetType(void) { return exml::typeAttribute; };
			virtual bool Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos);
			virtual bool Generate(etk::UString& _data, int32_t _indent);
		protected:
			etk::UString m_name;
		public:
			virtual void SetName(etk::UString _name) { m_name = _name; };
			virtual const etk::UString& GetName(void) { return m_name; };
	};
};


#endif


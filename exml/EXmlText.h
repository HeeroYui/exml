/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_XML_TEXT_H__
#define __ETK_XML_TEXT_H__

#include <exml/EXmlNode.h>
#include <etk/Vector.h>

namespace exml
{
	class EXmlText : public EXmlNode
	{
		public:
			EXmlText(void) { };
			virtual ~EXmlText(void) { };
			virtual nodeType_te GetType(void) const { return typeText; };
			virtual bool Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos);
			virtual bool Generate(etk::UString& _data, int32_t _indent) const;
			int32_t CountLines(void) const;
			virtual operator exml::EXmlText* () { return this; };
			virtual operator const exml::EXmlText* () const { return this; };
	};
	class EXmlTextCDATA : public EXmlText
	{
		public:
			EXmlTextCDATA(void) { };
			virtual ~EXmlTextCDATA(void) { };
			virtual nodeType_te GetType(void) { return typeText; };
			virtual bool Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos);
	};
};


#endif


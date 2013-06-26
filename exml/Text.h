/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_XML_TEXT_H__
#define __ETK_XML_TEXT_H__

#include <exml/Node.h>
#include <etk/Vector.h>

namespace exml
{
	class Text : public Node
	{
		public:
			Text(void) { };
			virtual ~Text(void) { };
			virtual nodeType_te GetType(void) const { return typeText; };
			virtual bool Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos);
			virtual bool Generate(etk::UString& _data, int32_t _indent) const;
			int32_t CountLines(void) const;
			virtual exml::Text* ToText(void) { return this; };
			virtual const exml::Text* ToText(void) const{ return this; };
	};
	class TextCDATA : public Text
	{
		public:
			TextCDATA(void) { };
			virtual ~TextCDATA(void) { };
			virtual nodeType_te GetType(void) { return typeText; };
			virtual bool Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos);
	};
};


#endif


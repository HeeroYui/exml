/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_XML_DECLARATION_H__
#define __ETK_XML_DECLARATION_H__

#include <exml/EXmlNode.h>
#include <etk/Vector.h>

namespace exml
{
	class EXmlDeclaration : public EXmlNode
	{
		public:
			EXmlDeclaration(void) { };
			virtual ~EXmlDeclaration(void) { };
			virtual nodeType_te GetType(void) const { return typeAttribute; };
			virtual bool Generate(etk::UString& _data, int32_t _indent) const;
			virtual bool Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos);
			virtual operator exml::EXmlDeclaration* () { return this; };
			virtual operator const exml::EXmlDeclaration* () const { return this; };
	};
};


#endif


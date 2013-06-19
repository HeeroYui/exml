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
			virtual nodeType_te GetType(void) { return typeAttribute; };
	};
};


#endif


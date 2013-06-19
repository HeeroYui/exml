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
			virtual nodeType_te GetType(void) { return typeText; };
	};
};


#endif


/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_XML_COMMENT_H__
#define __ETK_XML_COMMENT_H__

#include <exml/EXmlNode.h>
#include <etk/Vector.h>

namespace exml
{
	class EXmlElement : public EXmlNode
	{
		public:
			EXmlElement(void) { };
			virtual ~EXmlElement(void) { };
			virtual nodeType_te GetType(void) { return typeAttribute; };
	};
};


#endif


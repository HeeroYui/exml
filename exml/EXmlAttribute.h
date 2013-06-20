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
			virtual ~EXmlAttribute(void) { };
			virtual nodeType_te GetType(void) { return exml::typeAttribute; };
	};
};


#endif


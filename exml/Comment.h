/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_XML_COMMENT_H__
#define __ETK_XML_COMMENT_H__

#include <exml/Node.h>
#include <etk/Vector.h>

namespace exml
{
	class Comment : public Node
	{
		public:
			Comment(void) { };
			virtual ~Comment(void) { };
			virtual nodeType_te GetType(void) const { return typeAttribute; };
			virtual bool Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos);
			virtual bool Generate(etk::UString& _data, int32_t _indent) const;
			virtual exml::Comment* ToComment(void) { return this; };
			virtual const exml::Comment* ToComment(void) const { return this; };
	};
};


#endif


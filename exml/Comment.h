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
			/**
			 * @brief Constructor
			 */
			Comment(void) { };
			/**
			 * @brief Constructor
			 * @param[in] _value comment value
			 */
			Comment(const etk::UString& _value) : exml::Node(_value) { };
			/**
			 * @brief Destructor
			 */
			virtual ~Comment(void) { };
		public: // herited function:
			virtual nodeType_te GetType(void) const { return typeAttribute; };
			virtual bool Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc);
			virtual bool Generate(etk::UString& _data, int32_t _indent) const;
			virtual exml::Comment* ToComment(void) { return this; };
			virtual const exml::Comment* ToComment(void) const { return this; };
	};
};


#endif


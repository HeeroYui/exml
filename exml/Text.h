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
			/**
			 * @brief Constructor
			 */
			Text(void) { };
			/**
			 * @brief Constructor
			 * @param[in] _data String data of the current Text
			 */
			Text(const etk::UString& _data) : exml::Node(_data) { };
			/**
			 * @brief Destructor
			 */
			virtual ~Text(void) { };
			/**
			 * @brief Count the number of line in the current text
			 * @return The number of lines
			 */
			int32_t CountLines(void) const;
		public: // herited function:
			virtual nodeType_te GetType(void) const { return typeText; };
			virtual bool Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos);
			virtual bool Generate(etk::UString& _data, int32_t _indent) const;
			virtual exml::Text* ToText(void) { return this; };
			virtual const exml::Text* ToText(void) const{ return this; };
	};
	class TextCDATA : public Text
	{
		public:
			/**
			 * @brief Constructor
			 */
			TextCDATA(void) { };
			/**
			 * @brief Destructor
			 */
			virtual ~TextCDATA(void) { };
		public: // herited function:
			virtual bool Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos);
	};
};


#endif


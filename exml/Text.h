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
#include <vector>

namespace exml {
	class Text : public Node {
		public:
			/**
			 * @brief Constructor
			 */
			Text(void) { };
			/**
			 * @brief Constructor
			 * @param[in] _data String data of the current Text
			 */
			Text(const std::u32string& _data) : exml::Node(_data) { };
			/**
			 * @brief Destructor
			 */
			virtual ~Text(void) { };
			/**
			 * @brief count the number of line in the current text
			 * @return The number of lines
			 */
			int32_t countLines(void) const;
		public: // herited function:
			virtual enum nodeType getType(void) const {
				return typeText;
			};
			virtual bool iParse(const std::u32string& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc);
			virtual bool iGenerate(std::u32string& _data, int32_t _indent) const;
			virtual exml::Text* toText(void) {
				return this;
			};
			virtual const exml::Text* toText(void) const{
				return this;
			};
	};
	class TextCDATA : public Text {
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
			virtual bool iParse(const std::u32string& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc);
	};
};


#endif


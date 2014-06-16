/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ETK_XML_TEXT_H__
#define __ETK_XML_TEXT_H__

#include <exml/Node.h>
#include <vector>

namespace exml {
	class Text : public exml::Node {
		public:
			/**
			 * @brief Constructor
			 */
			Text() { };
			/**
			 * @brief Constructor
			 * @param[in] _data String data of the current Text
			 */
			Text(const std::string& _data) : exml::Node(_data) { };
			/**
			 * @brief Destructor
			 */
			virtual ~Text() { };
			/**
			 * @brief count the number of line in the current text
			 * @return The number of lines
			 */
			int32_t countLines() const;
		public: // herited function:
			virtual enum nodeType getType() const {
				return typeText;
			};
			virtual bool iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc);
			virtual bool iGenerate(std::string& _data, int32_t _indent) const;
			virtual exml::Text* toText() {
				return this;
			};
			virtual const exml::Text* toText() const{
				return this;
			};
	};
	class TextCDATA : public exml::Text {
		public:
			/**
			 * @brief Constructor
			 */
			TextCDATA() { };
			/**
			 * @brief Destructor
			 */
			virtual ~TextCDATA() { };
		public: // herited function:
			virtual bool iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc);
	};
};


#endif


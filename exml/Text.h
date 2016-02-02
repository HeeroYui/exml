/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <exml/Node.h>
#include <vector>

namespace exml {
	class Text : public exml::Node {
		protected:
			/**
			 * @brief Constructor
			 */
			Text() { };
			/**
			 * @brief Constructor
			 * @param[in] _data String data of the current Text
			 */
			Text(const std::string& _data) : exml::Node(_data) { };
		public:
			static std::shared_ptr<Text> create();
			static std::shared_ptr<Text> create(const std::string& _data);
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
			virtual std::shared_ptr<exml::Text> toText() {
				return std::static_pointer_cast<exml::Text>(shared_from_this());
			};
			virtual std::shared_ptr<const exml::Text> toText() const{
				return std::static_pointer_cast<const exml::Text>(shared_from_this());
			};
	};
	class TextCDATA : public exml::Text {
		protected:
			/**
			 * @brief Constructor
			 */
			TextCDATA() { };
		public:
			static std::shared_ptr<TextCDATA> create();
			/**
			 * @brief Destructor
			 */
			virtual ~TextCDATA() { };
		public: // herited function:
			virtual bool iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc);
			virtual bool iGenerate(std::string& _data, int32_t _indent) const;
	};
}


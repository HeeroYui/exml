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
	/**
	 * @brief Text node interface (internal data between two balise : &lt;XXX&gt; ALL here &lt;/XXX&gt;
	 */
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
			/**
			 * @brief defined factory
			 * @param[in] _data Data in the Text area
			 * @return Shared pointer on the Text element
			 */
			static ememory::SharedPtr<exml::Text> create(const std::string& _data="");
			/**
			 * @brief count the number of line in the current text
			 * @return The number of lines
			 */
			int32_t countLines() const;
		public:
			enum nodeType getType() const override{
				return nodeType_text;
			};
			bool iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::FilePos& _filePos, exml::Document& _doc) override;
			bool iGenerate(std::string& _data, int32_t _indent) const override;
			ememory::SharedPtr<exml::Text> toText() override {
				return std::static_pointer_cast<exml::Text>(shared_from_this());
			};
			ememory::SharedPtr<const exml::Text> toText() const override {
				return std::static_pointer_cast<const exml::Text>(shared_from_this());
			};
	};
	/**
	 * @brief Text node interface for balise CDATA &lt;![CDATA[*******]]&gt;
	 */
	class TextCDATA : public exml::Text {
		protected:
			/**
			 * @brief Constructor
			 */
			TextCDATA() { };
		public:
			/**
			 * @brief defined factory
			 * @return Shared pointer on the Text CDATA element
			 */
			static ememory::SharedPtr<TextCDATA> create();
		public:
			bool iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::FilePos& _filePos, exml::Document& _doc) override;
			bool iGenerate(std::string& _data, int32_t _indent) const override;
	};
}


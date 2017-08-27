/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <exml/internal/Node.hpp>
#include <etk/Vector.hpp>

namespace exml {
	namespace internal {
		/**
		 * @brief Text node interface (internal data between two balise : &lt;XXX&gt; ALL here &lt;/XXX&gt;
		 */
		class Text : public exml::internal::Node {
			protected:
				/**
				 * @brief Constructor
				 */
				Text() { };
				/**
				 * @brief Constructor
				 * @param[in] _data String data of the current Text
				 */
				Text(const etk::String& _data) : exml::internal::Node(_data) { };
			public:
				/**
				 * @brief defined factory
				 * @param[in] _data Data in the Text area
				 * @return Shared pointer on the Text element
				 */
				static ememory::SharedPtr<exml::internal::Text> create(const etk::String& _data="");
				/**
				 * @brief count the number of line in the current text
				 * @return The number of lines
				 */
				int32_t countLines() const;
			public:
				enum nodeType getType() const override{
					return nodeType::text;
				};
				bool iParse(const etk::String& _data,
				            int32_t& _pos,
				            bool _caseSensitive,
				            exml::FilePos& _filePos,
				            exml::internal::Document& _doc) override;
				bool iGenerate(etk::String& _data, int32_t _indent) const override;
				ememory::SharedPtr<exml::internal::Text> toText() override {
					return ememory::staticPointerCast<exml::internal::Text>(sharedFromThis());
				};
				const ememory::SharedPtr<exml::internal::Text> toText() const override {
					return ememory::staticPointerCast<exml::internal::Text>(sharedFromThis());
				};
		};
		/**
		 * @brief Text node interface for balise CDATA &lt;![CDATA[*******]]&gt;
		 */
		class TextCDATA : public exml::internal::Text {
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
				bool iParse(const etk::String& _data,
				            int32_t& _pos,
				            bool _caseSensitive,
				            exml::FilePos& _filePos,
				            exml::internal::Document& _doc) override;
				bool iGenerate(etk::String& _data, int32_t _indent) const override;
		};
	}
}


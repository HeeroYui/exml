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
		 * @brief Comment node: &lt;!-- ... --&gt;
		 */
		class Comment : public exml::internal::Node {
			public:
				/**
				 * @brief defined factory
				 * @return Shared pointer on the Comment element
				 * @param[in] _value comment value
				 */
				static ememory::SharedPtr<exml::internal::Comment> create(const etk::String& _value="");
				/**
				 * @brief Constructor
				 * @param[in] _value comment value
				 */
				Comment(const etk::String& _value) :
				  exml::internal::Node(_value) {
					
				}
			public:
				enum nodeType getType() const override {
					return nodeType::comment;
				}
				bool iParse(const etk::String& _data, int32_t& _pos, bool _caseSensitive, exml::FilePos& _filePos, exml::internal::Document& _doc) override;
				bool iGenerate(etk::String& _data, int32_t _indent) const override;
				ememory::SharedPtr<exml::internal::Comment> toComment() override {
					return ememory::staticPointerCast<exml::internal::Comment>(sharedFromThis());
				}
				const ememory::SharedPtr<exml::internal::Comment> toComment() const override {
					return ememory::staticPointerCast<exml::internal::Comment>(sharedFromThis());
				}
		};
	}
}


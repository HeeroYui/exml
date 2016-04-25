/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <exml/internal/Node.h>
#include <vector>

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
				static ememory::SharedPtr<exml::internal::Comment> create(const std::string& _value="");
				/**
				 * @brief Constructor
				 * @param[in] _value comment value
				 */
				Comment(const std::string& _value) :
				  exml::internal::Node(_value) {
					
				}
			public:
				enum nodeType getType() const override {
					return nodeType::comment;
				}
				bool iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::FilePos& _filePos, exml::internal::Document& _doc) override;
				bool iGenerate(std::string& _data, int32_t _indent) const override;
				ememory::SharedPtr<exml::internal::Comment> toComment() override {
					return std::static_pointer_cast<exml::internal::Comment>(shared_from_this());
				}
				ememory::SharedPtr<const exml::internal::Comment> toComment() const override {
					return std::static_pointer_cast<const exml::internal::Comment>(shared_from_this());
				}
		};
	}
}


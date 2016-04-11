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
	class Comment : public exml::Node {
		protected:
			/**
			 * @brief Constructor
			 */
			Comment() { };
		public:
			/**
			 * @brief defined factory
			 * @return Shared pointer on the Comment element
			 */
			static ememory::SharedPtr<exml::Comment> create();
			/**
			 * @brief Constructor
			 * @param[in] _value comment value
			 */
			Comment(const std::string& _value) :
			  exml::Node(_value) {
				
			};
		public:
			enum nodeType getType() const override {
				return typeAttribute;
			};
			bool iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::FilePos& _filePos, exml::Document& _doc) override;
			bool iGenerate(std::string& _data, int32_t _indent) const override;
			ememory::SharedPtr<exml::Comment> toComment() override {
				return std::static_pointer_cast<exml::Comment>(shared_from_this());
			};
			ememory::SharedPtr<const exml::Comment> toComment() const override {
				return std::static_pointer_cast<const exml::Comment>(shared_from_this());
			};
	};
}


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
	class Attribute : public exml::Node {
		protected:
			/**
			 * @brief Constructor
			 * @param[in] _name Name of the attribute.
			 * @param[in] _value Value of the attribute.
			 */
			Attribute(const std::string& _name="", const std::string& _value="");
		public:
			/**
			 * @brief defined factory
			 * @param[in] _name Name of the attribute
			 * @param[in] _value Value of the attribute
			 * @return Shared pointer on the Attribute element
			 */
			static ememory::SharedPtr<Attribute> create(const std::string& _name="", const std::string& _value="");
		protected:
			std::string m_name; //!< Name of the attribute
		public:
			/**
			 * @brief set the name of the attribute
			 * @param[in] _name New name of the attribute
			 */
			virtual void setName(const std::string& _name) {
				m_name = _name;
			};
			/**
			 * @brief get the current name of the Attribute
			 * @return String of the attribute
			 */
			virtual const std::string& getName() const {
				return m_name;
			};
		public:
			enum nodeType getType() const override {
				return exml::typeAttribute;
			};
			bool iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::FilePos& _filePos, exml::Document& _doc) override;
			bool iGenerate(std::string& _data, int32_t _indent) const override;
			ememory::SharedPtr<exml::Attribute> toAttribute() override {
				return std::static_pointer_cast<exml::Attribute>(shared_from_this());
			};
			ememory::SharedPtr<const exml::Attribute> toAttribute() const override {
				return std::static_pointer_cast<const exml::Attribute>(shared_from_this());
			};
			void clear() override;
	};
}


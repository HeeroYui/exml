/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <exml/internal/AttributeList.h>

namespace exml {
	namespace internal {
		/**
		 * @brief Declaration node: &lt;?XXXXXX ... &gt;
		 */
		class Declaration : public exml::internal::AttributeList {
			protected:
				/**
				 * @brief Constructor
				 * @param[in] _name name of the declaration (xml, xml:xxxx ...)
				 */
				Declaration(const std::string& _name="") :
				  exml::internal::AttributeList(_name) {
					
				};
			public:
				/**
				 * @brief Factory to create declaration
				 * @param[in] _name name of the declaration (xml, xml:xxxx ...)
				 * @return a structure declaration
				 */
				static ememory::SharedPtr<Declaration> create(const std::string& _name="");
			public:
				enum nodeType getType() const override{
					return nodeType::declaration;
				};
				bool iGenerate(std::string& _data, int32_t _indent) const override;
				bool iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::FilePos& _filePos, exml::internal::Document& _doc) override;
				ememory::SharedPtr<exml::internal::Declaration> toDeclaration() override {
					return std::static_pointer_cast<exml::internal::Declaration>(shared_from_this());
				};
				ememory::SharedPtr<const exml::internal::Declaration> toDeclaration() const override {
					return std::static_pointer_cast<const exml::internal::Declaration>(shared_from_this());
				};
		};
		/**
		 * @brief Declaration node: &lt;?XML ... &gt;
		 */
		class DeclarationXML : public exml::internal::Declaration {
			public:
				/**
				 * @brief Constructor for the generic declaration : <?xml version="" format="UTF-8"?>
				 * @param[in] _version Xml version.
				 * @param[in] _format charset of the XML
				 * @param[in] _standalone this document is standalone
				 */
				DeclarationXML(const std::string& _version, const std::string& _format = "UTF-8", bool _standalone = true);
			public:
				/**
				 * @brief Factory to create XML declaration
				 * @param[in] _version Xml version.
				 * @param[in] _format charset of the XML
				 * @param[in] _standalone this document is standalone
				 * @return a structure declaration
				 */
				static ememory::SharedPtr<DeclarationXML> create(const std::string& _version, const std::string& _format = "UTF-8", bool _standalone = true);
		};
	}
}


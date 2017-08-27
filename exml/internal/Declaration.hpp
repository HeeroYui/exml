/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <exml/internal/AttributeList.hpp>

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
				Declaration(const etk::String& _name="") :
				  exml::internal::AttributeList(_name) {
					
				};
			public:
				/**
				 * @brief Factory to create declaration
				 * @param[in] _name name of the declaration (xml, xml:xxxx ...)
				 * @return a structure declaration
				 */
				static ememory::SharedPtr<Declaration> create(const etk::String& _name="");
			public:
				enum nodeType getType() const override{
					return nodeType::declaration;
				};
				bool iGenerate(etk::String& _data, int32_t _indent) const override;
				bool iParse(const etk::String& _data, int32_t& _pos, bool _caseSensitive, exml::FilePos& _filePos, exml::internal::Document& _doc) override;
				ememory::SharedPtr<exml::internal::Declaration> toDeclaration() override {
					return ememory::staticPointerCast<exml::internal::Declaration>(sharedFromThis());
				};
				const ememory::SharedPtr<exml::internal::Declaration> toDeclaration() const override {
					return ememory::staticPointerCast<exml::internal::Declaration>(sharedFromThis());
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
				DeclarationXML(const etk::String& _version, const etk::String& _format = "UTF-8", bool _standalone = true);
			public:
				/**
				 * @brief Factory to create XML declaration
				 * @param[in] _version Xml version.
				 * @param[in] _format charset of the XML
				 * @param[in] _standalone this document is standalone
				 * @return a structure declaration
				 */
				static ememory::SharedPtr<DeclarationXML> create(const etk::String& _version, const etk::String& _format = "UTF-8", bool _standalone = true);
		};
	}
}


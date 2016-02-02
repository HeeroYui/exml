/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <exml/AttributeList.h>

namespace exml {
	class Declaration : public exml::AttributeList {
		protected:
			/**
			 * @brief Constructor
			 */
			Declaration() { };
			/**
			 * @brief Constructor
			 * @param[in] _name name of the declaration (xml, xml:xxxx ...)
			 */
			Declaration(const std::string& _name) :
			  exml::AttributeList(_name) {
				
			};
		public:
			static std::shared_ptr<Declaration> create();
			static std::shared_ptr<Declaration> create(const std::string& _name);
			/**
			 * @brief Destructor
			 */
			virtual ~Declaration() { };
		public: // herited function:
			virtual enum nodeType getType() const {
				return typeAttribute;
			};
			virtual bool iGenerate(std::string& _data, int32_t _indent) const;
			virtual bool iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc);
			virtual std::shared_ptr<exml::Declaration> toDeclaration() {
				return std::static_pointer_cast<exml::Declaration>(shared_from_this());
			};
			virtual std::shared_ptr<const exml::Declaration> toDeclaration() const {
				return std::static_pointer_cast<const exml::Declaration>(shared_from_this());
			};
	};
	class DeclarationXML : public exml::Declaration {
		public:
			/**
			 * @brief Constructor for the generic declaration : <?xml version="" format="UTF-8"?>
			 * @param[in] _version Xml version.
			 * @param[in] _format charset of the XML
			 * @param[in] _standalone this document is standalone
			 */
			DeclarationXML(const std::string& _version, const std::string& _format = "UTF-8", bool _standalone = true);
		public:
			static std::shared_ptr<DeclarationXML> create(const std::string& _version, const std::string& _format = "UTF-8", bool _standalone = true);
			/**
			 * @brief Destructor
			 */
			virtual ~DeclarationXML() { };
	};
}


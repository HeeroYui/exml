/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <exml/Node.hpp>
#include <exml/AttributeList.hpp>

namespace exml {
	/**
	 * @brief Declaration node: &lt;?XXXXXX ... &gt;
	 */
	class Declaration : public exml::AttributeList {
		public:
			/**
			 * @brief Constructor
			 * @param[in] _internalNode Internal Node to set data
			 */
			Declaration(ememory::SharedPtr<exml::internal::Node> _internalNode);
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 */
			Declaration(const exml::Declaration& _obj);
			/**
			 * @brief Constructor
			 * @param[in] _name name of the declaration (xml, xml:xxxx ...)
			 */
			Declaration(const std::string& _name="");
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 * @return A reference on the local Object
			 */
			exml::Declaration& operator= (const exml::Declaration& _obj);
	};
	/**
	 * @brief Declaration node: &lt;?XML ... &gt;
	 */
	class DeclarationXML : public exml::Declaration {
		public:
			/**
			 * @brief Constructor
			 * @param[in] _internalNode Internal Node to set data
			 */
			DeclarationXML(ememory::SharedPtr<exml::internal::Node> _internalNode);
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 */
			DeclarationXML(const exml::DeclarationXML& _obj);
			/**
			 * @brief Constructor for the generic declaration : <?xml version="" format="UTF-8"?>
			 * @param[in] _version Xml version.
			 * @param[in] _format charset of the XML
			 * @param[in] _standalone this document is standalone
			 */
			DeclarationXML(const std::string& _version="0.0", const std::string& _format = "UTF-8", bool _standalone = true);
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 * @return A reference on the local Object
			 */
			exml::DeclarationXML& operator= (const exml::DeclarationXML& _obj);
	};
}


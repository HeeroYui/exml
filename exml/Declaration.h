/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_XML_DECLARATION_H__
#define __ETK_XML_DECLARATION_H__

#include <exml/AttributeList.h>

namespace exml
{
	class Declaration : public exml::AttributeList
	{
		public:
			/**
			 * @brief Constructor
			 */
			Declaration(void) { };
			/**
			 * @brief Constructor for the generic declaration : <?xml version="" format="UTF-8"?>
			 * @param[in] _version Xml version.
			 * @param[in] _format charset of the XML
			 * @param[in] _standalone this document is standalone
			 */
			// for xml generic declaration
			Declaration(const etk::UString& _version, unicode::charset_te _format=unicode::EDN_CHARSET_UTF8, bool _standalone=true);
			/**
			 * @brief Destructor
			 */
			virtual ~Declaration(void) { };
		public: // herited function:
			virtual nodeType_te GetType(void) const { return typeAttribute; };
			virtual bool Generate(etk::UString& _data, int32_t _indent) const;
			virtual bool Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos);
			virtual exml::Declaration* ToDeclaration(void) { return this; };
			virtual const exml::Declaration* ToDeclaration(void) const { return this; };
	};
};


#endif


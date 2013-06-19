/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_XML_DOCUMENT_H__
#define __ETK_XML_DOCUMENT_H__

#include <exml/EXmlElement.h>
#include <etk/unicode.h>
#include <etk/Vector.h>

namespace exml
{
	class EXmlDocument : exml::EXmlElement
	{
		public:
			EXmlDocument(void);
			virtual ~EXmlDocument(void) { };
			virtual nodeType_te GetType(void) { return typeDocument; };
		private:
			unicode::charset_te m_charset;
		public:
			virtual void SetCharset(unicode::charset_te _charset) { m_charset = _charset; };
			virtual unicode::charset_te GetCharset(void) { return m_charset; };
		private:
			bool m_caseSensitive;
		public:
			virtual void SetCaseSensitive(bool _val) { m_caseSensitive = _val; };
			virtual bool GetCaseSensitive(void) { return m_caseSensitive; };
		public:
			/**
			 * @brief Parse a string that contain an XML
			 * @param[in] _data Data to parse
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool Parse(const etk::UString& _data);
			/**
			 * @brief Generate a string that contain the created XML
			 * @param[out] _data Data where the xml is stored
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool Generate(etk::UString& _data);
			/**
			 * @brief Load the file that might contain the xml
			 * @param[in] _file Filename of the xml (compatible with etk FSNode naming)
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool Load(const etk::UString& _file);
			/**
			 * @brief Store the Xml in the file
			 * @param[in] _file Filename of the xml (compatible with etk FSNode naming)
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool Store(const etk::UString& _file);
			
	};
};


#endif



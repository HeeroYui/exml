/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_XML_DOCUMENT_H__
#define __ETK_XML_DOCUMENT_H__

#include <exml/Element.h>
#include <etk/unicode.h>
#include <etk/Vector.h>

namespace exml
{
	class Document : public exml::Element
	{
		public:
			/**
			 * @brief Constructor
			 */
			Document(void);
			/**
			 * @brief Destructor
			 */
			virtual ~Document(void) { };
		private:
			unicode::charset_te m_charset;
		public:
			/**
			 * @brief Get the current charset of the Parsing
			 * @param[in] _charset The new charset
			 */
			virtual void SetCharset(unicode::charset_te _charset) { m_charset = _charset; };
			/**
			 * @brief Get the current charset of the Parsing
			 * @return The current charset
			 */
			virtual unicode::charset_te GetCharset(void) const { return m_charset; };
		private:
			bool m_caseSensitive; // check the case sensitive of the nodes and attribute
		public:
			/**
			 * @brief Enable or diasable the case sensitive (must be done before the call of parsing)
			 * @param[in] _val true if enable; false else.
			 */
			virtual void SetCaseSensitive(bool _val) { m_caseSensitive = _val; };
			/**
			 * @brief Get the status of case sensitive mode.
			 * @return true if case sensitive is active
			 */
			virtual bool GetCaseSensitive(void) const { return m_caseSensitive; };
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
			/**
			 * @brief Display the Document on console
			 */
			void Display(void);
		private:
			bool m_writeErrorWhenDetexted;
			etk::UString m_comment;
			etk::UString m_Line;
			exml::filePos m_filePos;
		public:
			void DisplayErrorWhenDetected(void) { m_writeErrorWhenDetexted=true; };
			void NotDisplayErrorWhenDetected(void) { m_writeErrorWhenDetexted=false; };
			
			void CreateError(const etk::UString& _data, int32_t _pos, const exml::filePos& _filePos, const etk::UString& _comment);
			void DisplayError(void);
		public: // herited function:
			virtual nodeType_te GetType(void) const { return typeDocument; };
			bool IGenerate(etk::UString& _data, int32_t _indent) const;
			virtual exml::Document* ToDocument(void) { return this; };
			virtual const exml::Document* ToDocument(void) const { return this; };
	};
};

/*
#define CREATE_ERROR(doc,data,pos,filePos,comment) \
	EXML_ERROR( (pos) << " " << (comment) << "\n" \
	           << (data).ExtractLine((pos)) << "\n" \
	           << CreatePosPointer((filePos).GetCol()) )
*/
#define CREATE_ERROR(doc,data,pos,filePos,comment) \
	do { \
		EXML_ERROR(comment); \
		(doc).CreateError((data),(pos),(filePos),(comment)); \
	} while (0)

//__LINE__, __class__, __func__

#endif



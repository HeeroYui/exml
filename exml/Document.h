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
#include <vector>

namespace exml {
	class Document : public exml::Element {
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
			bool m_caseSensitive; // check the case sensitive of the nodes and attribute
		public:
			/**
			 * @brief Enable or diasable the case sensitive (must be done before the call of parsing)
			 * @param[in] _val true if enable; false else.
			 */
			virtual void setCaseSensitive(bool _val) {
				m_caseSensitive = _val;
			};
			/**
			 * @brief get the status of case sensitive mode.
			 * @return true if case sensitive is active
			 */
			virtual bool getCaseSensitive(void) const {
				return m_caseSensitive;
			};
		public:
			/**
			 * @brief parse a string that contain an XML
			 * @param[in] _data Data to parse
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool parse(const std::string& _data);
			/**
			 * @brief generate a string that contain the created XML
			 * @param[out] _data Data where the xml is stored
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool generate(std::string& _data);
			/**
			 * @brief Load the file that might contain the xml
			 * @param[in] _file Filename of the xml (compatible with etk FSNode naming)
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool load(const std::string& _file);
			/**
			 * @brief Store the Xml in the file
			 * @param[in] _file Filename of the xml (compatible with etk FSNode naming)
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool store(const std::string& _file);
			/**
			 * @brief Display the Document on console
			 */
			void display(void);
		private:
			bool m_writeErrorWhenDetexted;
			std::string m_comment;
			std::string m_Line;
			exml::filePos m_filePos;
		public:
			void displayErrorWhenDetected(void) {
				m_writeErrorWhenDetexted = true;
			};
			void notDisplayErrorWhenDetected(void) {
				m_writeErrorWhenDetexted = false;
			};
			
			void createError(const std::string& _data, int32_t _pos, const exml::filePos& _filePos, const std::string& _comment);
			void displayError(void);
		public: // herited function:
			virtual enum nodeType getType(void) const {
				return typeDocument;
			};
			bool iGenerate(std::string& _data, int32_t _indent) const;
			virtual exml::Document* toDocument(void) {
				return this;
			};
			virtual const exml::Document* toDocument(void) const {
				return this;
			};
	};
};

/*
#define CREATE_ERROR(doc,data,pos,filePos,comment) \
	EXML_ERROR( (pos) << " " << (comment) << "\n" \
	           << (data).ExtractLine((pos)) << "\n" \
	           << CreatePosPointer((filePos).getCol()) )
*/
#define CREATE_ERROR(doc,data,pos,filePos,comment) \
	do { \
		EXML_ERROR(comment); \
		(doc).createError((data),(pos),(filePos),(comment)); \
	} while (0)

//__LINE__, __class__, __func__

#endif



/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <exml/internal/Element.h>
#include <vector>

namespace exml {
	namespace internal {
		/**
		 * @brief Basic document element of a document
		 */
		class Document : public exml::internal::Element {
			public:
				/**
				 * @brief Constructor
				 */
				Document();
				/**
				 * @brief Factory on a document
				 * @return an local created xml document
				 */
				static ememory::SharedPtr<exml::internal::Document> create();
			private:
				bool m_caseSensitive; //!< check the case sensitive of the nodes and attribute
			public:
				/**
				 * @brief Enable or diasable the case sensitive (must be done before the call of parsing)
				 * @param[in] _val true if enable; false else.
				 */
				// TODO: Naming error, it is insensitive ...
				virtual void setCaseSensitive(bool _val) {
					m_caseSensitive = _val;
				};
				/**
				 * @brief get the status of case sensitive mode.
				 * @return true if case sensitive is active
				 */
				virtual bool getCaseSensitive() const {
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
				void display();
			private:
				bool m_writeErrorWhenDetexted; //!< Request print error in parsing just when detected
				std::string m_comment; //!< Comment on the error
				std::string m_Line; //!< Parse line error (copy)
				exml::FilePos m_filePos; //!< position of the error
			public:
				/**
				 * @brief Request display error when detected (not print only at the end ...)
				 */
				void displayErrorWhenDetected() {
					m_writeErrorWhenDetexted = true;
				}
				/**
				 * @brief Request NOT display error when detected.
				 */
				void notDisplayErrorWhenDetected() {
					m_writeErrorWhenDetexted = false;
				}
				/**
				 * @brief Create an error in the parsing (call by the syetm for error management)
				 * @param[in] _data string of chat is wrong
				 * @param[in] _pos Position in the file
				 * @param[in] _filePos human position of the error
				 * @param[in] _comment Error string to display
				 */
				void createError(const std::string& _data, int32_t _pos, const exml::FilePos& _filePos, const std::string& _comment);
				/**
				 * @brief request display in log of the error
				 */
				void displayError();
			public:
				enum nodeType getType() const override {
					return nodeType_document;
				}
				bool iGenerate(std::string& _data, int32_t _indent) const override;
				ememory::SharedPtr<exml::internal::Document> toDocument() override {
					return std::static_pointer_cast<exml::internal::Document>(shared_from_this());
				}
				ememory::SharedPtr<const exml::internal::Document> toDocument() const override {
					return std::static_pointer_cast<const exml::internal::Document>(shared_from_this());
				}
		};
	}
}

#define CREATE_ERROR(doc,data,pos,filePos,comment) \
	do { \
		EXML_ERROR(comment); \
		(doc).createError((data),(pos),(filePos),(comment)); \
	} while (0)

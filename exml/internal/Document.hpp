/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <exml/internal/Element.hpp>
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
				 * @brief Set the display of the error when detected.
				 * @param[in] _value true: display error, false not display error (get it at end)
				 */
				void setDisplayError(bool _value);
				/**
				 * @brief Get the display of the error status.
				 * @return true Display error
				 * @return false Does not display error (get it at end)
				 */
				bool getDisplayError();
				/**
				 * @brief Request display in log of the error
				 */
				void displayError();
				/**
				 * @brief Create an error in the parsing (call by the syetm for error management)
				 * @param[in] _data string of chat is wrong
				 * @param[in] _pos Position in the file
				 * @param[in] _filePos human position of the error
				 * @param[in] _comment Error string to display
				 */
				void createError(const std::string& _data, int32_t _pos, const exml::FilePos& _filePos, const std::string& _comment);
			public:
				enum nodeType getType() const override {
					return nodeType::document;
				}
				bool iGenerate(std::string& _data, int32_t _indent) const override;
				ememory::SharedPtr<exml::internal::Document> toDocument() override {
					return ememory::staticPointerCast<exml::internal::Document>(sharedFromThis());
				}
				const ememory::SharedPtr<exml::internal::Document> toDocument() const override {
					return ememory::staticPointerCast<exml::internal::Document>(sharedFromThis());
				}
		};
	}
}

/**
 * @brief Automatic create error on the basic Document object
 * @param[in] doc Document reference
 * @param[in] data main string parsed
 * @param[in] pos Position in the file
 * @param[in] filePos position in linre row in the file
 * @param[in] comment Comment of the error find
 */
#define CREATE_ERROR(doc,data,pos,filePos,comment) \
	do { \
		EXML_ERROR(comment); \
		(doc).createError((data),(pos),(filePos),(comment)); \
	} while (0)

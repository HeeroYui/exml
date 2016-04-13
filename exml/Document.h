/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <exml/Element.h>
#include <vector>

namespace exml {
	/**
	 * @brief Basic document element of a document
	 */
	class Document : public exml::Element {
		public:
			/**
			 * @brief Constructor
			 * @param[in] _internalNode Internal Node to set data
			 */
			Document(ememory::SharedPtr<exml::internal::Node> _internalNode);
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 */
			Document(const exml::Document& _obj);
			/**
			 * @brief Constructor
			 */
			Document();
			/**
			 * @brief Copy constructor
			 * @param[in] _obj Object to copy
			 */
			exml::Document& operator= (const exml::Document& _obj);
			/**
			 * @brief Enable or diasable the case sensitive (must be done before the call of parsing)
			 * @param[in] _val true if enable; false else.
			 */
			void setCaseSensitive(bool _val);
			/**
			 * @brief get the status of case sensitive mode.
			 * @return true if case sensitive is active
			 */
			virtual bool getCaseSensitive() const;
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
			/**
			 * @brief Request display error when detected (not print only at the end ...)
			 */
			void displayErrorWhenDetected();
			/**
			 * @brief Request NOT display error when detected.
			 */
			void notDisplayErrorWhenDetected();
			/**
			 * @brief request display in log of the error
			 */
			void displayError();
	};
};

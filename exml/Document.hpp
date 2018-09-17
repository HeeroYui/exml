/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <exml/Element.hpp>
#include <etk/Vector.hpp>
#include <etk/uri/uri.hpp>

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
			 * @return Reference on the local Object
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
			bool parse(const etk::String& _data);
			/**
			 * @brief generate a string that contain the created XML
			 * @param[out] _data Data where the xml is stored
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool generate(etk::String& _data);
			/**
			 * @brief Load the file that might contain the xml
			 * @param[in] _path/_uri Path/URI of the xml
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool load(const etk::Path& _path);
			/// @previous
			bool load(const etk::Uri& _uri);
			/**
			 * @brief Store the Xml in the file
			 * @param[in] _path/_uri Path/URI of the xml
			 * @return false : An error occured
			 * @return true : Parsing is OK
			 */
			bool store(const etk::Path& _path);
			/// @previous
			bool store(const etk::Uri& _uri);
			/**
			 * @brief Display the Document on console
			 */
			void display();
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
			 * @brief Display error detected.
			 */
			void displayError();
	};
};

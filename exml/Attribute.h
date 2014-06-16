/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ETK_XML_ATTRIBUTE_H__
#define __ETK_XML_ATTRIBUTE_H__

#include <exml/Node.h>
#include <vector>

namespace exml {
	class Attribute : public exml::Node {
		public:
			/**
			 * @brief Constructor
			 */
			Attribute() { };
			/**
			 * @brief Constructor
			 * @param[in] _name Name of the attribute.
			 * @param[in] _value Value of the attribute.
			 */
			Attribute(const std::string& _name, const std::string& _value);
			/**
			 * @brief Destructor
			 */
			virtual ~Attribute() { };
		protected:
			std::string m_name;
		public:
			/**
			 * @brief set the name of the attribute
			 * @param[in] _name New name of the attribute
			 */
			virtual void setName(const std::string& _name) {
				m_name = _name;
			};
			/**
			 * @brief get the current name of the Attribute
			 * @return String of the attribute
			 */
			virtual const std::string& getName() const {
				return m_name;
			};
		public: // herited function:
			virtual enum nodeType getType() const {
				return exml::typeAttribute;
			};
			virtual bool iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc);
			virtual bool iGenerate(std::string& _data, int32_t _indent) const;
			virtual exml::Attribute* toAttribute() {
				return this;
			};
			virtual const exml::Attribute* toAttribute() const {
				return this;
			};
			virtual void clear();
	};
};


#endif


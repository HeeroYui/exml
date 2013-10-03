/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_XML_ATTRIBUTE_H__
#define __ETK_XML_ATTRIBUTE_H__

#include <exml/Node.h>
#include <etk/Vector.h>

namespace exml
{
	class Attribute : public Node
	{
		public:
			/**
			 * @brief Constructor
			 */
			Attribute(void) { };
			/**
			 * @brief Constructor
			 * @param[in] _name Name of the attribute.
			 * @param[in] _value Value of the attribute.
			 */
			Attribute(const etk::UString& _name, const etk::UString& _value);
			/**
			 * @brief Destructor
			 */
			virtual ~Attribute(void) { };
		protected:
			etk::UString m_name;
		public:
			/**
			 * @brief set the name of the attribute
			 * @param[in] _name New name of the attribute
			 */
			virtual void setName(etk::UString _name) { m_name = _name; };
			/**
			 * @brief get the current name of the Attribute
			 * @return String of the attribute
			 */
			virtual const etk::UString& getName(void) const { return m_name; };
		public: // herited function:
			virtual nodeType_te getType(void) const { return exml::typeAttribute; };
			virtual bool iParse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc);
			virtual bool iGenerate(etk::UString& _data, int32_t _indent) const;
			virtual exml::Attribute* toAttribute(void) { return this; };
			virtual const exml::Attribute* toAttribute(void) const { return this; };
			virtual void clear(void);
	};
};


#endif


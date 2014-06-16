/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __ETK_XML_COMMENT_H__
#define __ETK_XML_COMMENT_H__

#include <exml/Node.h>
#include <vector>

namespace exml {
	class Comment : public exml::Node {
		public:
			/**
			 * @brief Constructor
			 */
			Comment() { };
			/**
			 * @brief Constructor
			 * @param[in] _value comment value
			 */
			Comment(const std::string& _value) :
			  exml::Node(_value) {
				
			};
			/**
			 * @brief Destructor
			 */
			virtual ~Comment() { };
		public: // herited function:
			virtual enum nodeType getType() const {
				return typeAttribute;
			};
			virtual bool iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc);
			virtual bool iGenerate(std::string& _data, int32_t _indent) const;
			virtual exml::Comment* toComment() {
				return this;
			};
			virtual const exml::Comment* toComment() const {
				return this;
			};
	};
};


#endif


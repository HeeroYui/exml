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
		protected:
			/**
			 * @brief Constructor
			 */
			Comment() { };
		public:
			static std::shared_ptr<Comment> create();
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
			virtual std::shared_ptr<exml::Comment> toComment() {
				return std::static_pointer_cast<exml::Comment>(shared_from_this());
			};
			virtual std::shared_ptr<const exml::Comment> toComment() const {
				return std::static_pointer_cast<const exml::Comment>(shared_from_this());
			};
	};
};


#endif


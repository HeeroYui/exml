/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_XML_ATTRIBUTE_LIST_H__
#define __ETK_XML_ATTRIBUTE_LIST_H__

#include <exml/Node.h>
#include <etk/Vector.h>
#include <exml/Attribute.h>

namespace exml
{
	class AttributeList : public Node
	{
		public:
			AttributeList(void) { };
			virtual ~AttributeList(void) { };
		protected:
			etk::Vector<exml::Attribute*> m_listAttribute;
		public:
			int32_t SizeAttribute(void) const { return m_listAttribute.Size(); };
			void AppendAttribute(Attribute* _node);
			Attribute* GetAttr(int32_t _id);
			const Attribute* GetAttr(int32_t _id) const;
			const etk::UString& GetAttribute(const etk::UString& _name) const;
			void SetAttribute(const etk::UString& _name, const etk::UString& _value);
		public:
			// herited function:
			bool Generate(etk::UString& _data, int32_t _indent) const;
	};
};


#endif


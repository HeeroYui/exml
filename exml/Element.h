/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_XML_ELEMENT_H__
#define __ETK_XML_ELEMENT_H__

#include <exml/Node.h>
#include <etk/Vector.h>
#include <exml/Attribute.h>

namespace exml
{
	class Element : public Node
	{
		public:
			Element(void) { };
			Element(const etk::UString& _value) : exml::Node(_value) { };
			virtual ~Element(void) { };
			virtual nodeType_te GetType(void) const { return typeElement; };
		protected:
			etk::Vector<exml::Node*> m_listSub;
		public:
			int32_t Size(void) const { return m_listSub.Size(); };
			void Append(Node* _node);
			Node* Get(int32_t _id);
			const Node* Get(int32_t _id) const;
			Node* GetNamed(const etk::UString& _name);
			const Node* GetNamed(const etk::UString& _name) const;
		protected:
			etk::Vector<exml::Attribute*> m_listAttribute;
		public:
			int32_t SizeAttribute(void) const { return m_listSub.Size(); };
			void AppendAttribute(Attribute* _node);
			Attribute* GetAttr(int32_t _id);
			const Attribute* GetAttr(int32_t _id) const;
			const etk::UString& GetAttribute(const etk::UString& _name) const;
		public:
			virtual bool Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos);
			virtual bool Generate(etk::UString& _data, int32_t _indent) const;
		protected:
			bool SubParse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos, bool _mainNode=false);
			virtual operator exml::Element* () { return this; };
			virtual operator const exml::Element* () const { return this; };
	};
};


#endif


/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __ETK_XML_ELEMENT_H__
#define __ETK_XML_ELEMENT_H__

#include <exml/EXmlNode.h>
#include <etk/Vector.h>
#include <exml/EXmlAttribute.h>

namespace exml
{
	class EXmlElement : public EXmlNode
	{
		public:
			EXmlElement(void) { };
			EXmlElement(const etk::UString& _value) : exml::EXmlNode(_value) { };
			virtual ~EXmlElement(void) { };
			virtual nodeType_te GetType(void) const { return typeElement; };
		protected:
			etk::Vector<exml::EXmlNode*> m_listSub;
		public:
			int32_t SizeSub(void) const { return m_listSub.Size(); };
			void AppendSub(EXmlNode* _node);
			EXmlNode* GetSub(int32_t _id);
			const EXmlNode* GetSub(int32_t _id) const;
			EXmlNode* GetNode(const etk::UString& _name);
			const EXmlNode* GetNode(const etk::UString& _name) const;
		protected:
			etk::Vector<exml::EXmlAttribute*> m_listAttribute;
		public:
			int32_t SizeAttribute(void) const { return m_listSub.Size(); };
			void AppendAttribute(EXmlAttribute* _node);
			EXmlAttribute* GetAttr(int32_t _id);
			const EXmlAttribute* GetAttr(int32_t _id) const;
			const etk::UString& GetAttribute(const etk::UString& _name) const;
		public:
			virtual bool Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos);
			virtual bool Generate(etk::UString& _data, int32_t _indent) const;
		protected:
			bool SubParse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos, bool _mainNode=false);
			virtual operator exml::EXmlElement* () { return this; };
			virtual operator const exml::EXmlElement* () const { return this; };
	};
};


#endif


/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <exml/Element.h>
#include <exml/debug.h>
#include <exml/Text.h>
#include <exml/Comment.h>
#include <exml/Attribute.h>
#include <exml/Declaration.h>
#include <exml/Document.h>

#undef __class__
#define __class__	"Element"


exml::Element::~Element(void)
{
	for (int32_t iii=0; iii<m_listSub.Size(); iii++) {
		if (NULL!=m_listSub[iii]) {
			delete(m_listSub[iii]);
			m_listSub[iii]=NULL;
		}
	}
	m_listSub.Clear();
}



exml::nodeType_te exml::Element::GetType(int32_t _id)
{
	exml::Node* tmpp = GetNode(_id);
	if (NULL==tmpp) {
		return exml::typeUnknow;
	}
	return tmpp->GetType();
}
const exml::nodeType_te exml::Element::GetType(int32_t _id) const
{
	const exml::Node* tmpp = GetNode(_id);
	if (NULL==tmpp) {
		return exml::typeUnknow;
	}
	return tmpp->GetType();
}


exml::Node* exml::Element::GetNode(int32_t _id)
{
	if (_id <0 || _id>m_listSub.Size()) {
		return NULL;
	}
	return m_listSub[_id];
}
const exml::Node* exml::Element::GetNode(int32_t _id) const
{
	if (_id <0 || _id>m_listSub.Size()) {
		return NULL;
	}
	return m_listSub[_id];
}


exml::Element* exml::Element::GetElement(int32_t _id)
{
	exml::Node* tmpp = GetNode(_id);
	if (NULL==tmpp) {
		return NULL;
	}
	return tmpp->ToElement();
}
const exml::Element* exml::Element::GetElement(int32_t _id) const
{
	const exml::Node* tmpp = GetNode(_id);
	if (NULL==tmpp) {
		return NULL;
	}
	return tmpp->ToElement();
}


exml::Element* exml::Element::GetNamed(const etk::UString& _name)
{
	if (_name.Size()==0) {
		return NULL;
	}
	for (int32_t iii=0; iii<m_listSub.Size(); iii++) {
		if(    NULL != m_listSub[iii]
		    && m_listSub[iii]->GetType() == exml::typeElement
		    && m_listSub[iii]->GetValue() == _name) {
			if (NULL==m_listSub[iii]) {
				return NULL;
			}
			return m_listSub[iii]->ToElement();
		}
	}
	return NULL;
}
const exml::Element* exml::Element::GetNamed(const etk::UString& _name) const
{
	if (_name.Size()==0) {
		return NULL;
	}
	for (int32_t iii=0; iii<m_listSub.Size(); iii++) {
		if(    NULL != m_listSub[iii]
		    && m_listSub[iii]->GetType() == exml::typeElement
		    && m_listSub[iii]->GetValue() == _name) {
			if (NULL==m_listSub[iii]) {
				return NULL;
			}
			return m_listSub[iii]->ToElement();
		}
	}
	return NULL;
}

void exml::Element::Append(exml::Node* _node)
{
	if (_node == NULL) {
		EXML_ERROR("Try to set an empty node");
		return;
	}
	if (_node->GetType()==exml::typeAttribute) {
		AppendAttribute(_node->ToAttribute());
		return;
	}
	for (int32_t iii=0; iii<m_listSub.Size(); iii++) {
		if (m_listSub[iii] == _node) {
			EXML_ERROR("Try to add a node that is already added before !!!");
			return;
		}
	}
	m_listSub.PushBack(_node);
}

etk::UString exml::Element::GetText(void)
{
	// TODO : Add more capabilities ...
	etk::UString res;
	for (int32_t iii=0; iii<m_listSub.Size(); iii++) {
		if (NULL!=m_listSub[iii]) {
			m_listSub[iii]->IGenerate(res, 0);
		}
	}
	return res;
}


bool exml::Element::IGenerate(etk::UString& _data, int32_t _indent) const
{
	AddIndent(_data, _indent);
	_data += "<";
	_data += m_value;
	exml::AttributeList::IGenerate(_data, _indent);
	
	if (m_listSub.Size()>0) {
		if(    m_listSub.Size()==1
		    && m_listSub[0] != NULL
		    && m_listSub[0]->GetType() == exml::typeText
		    && static_cast<exml::Text*>(m_listSub[0])->CountLines()==1) {
			_data += ">";
			m_listSub[0]->IGenerate(_data,0);
		} else {
			_data += ">\n";
			
			for (int32_t iii=0; iii<m_listSub.Size(); iii++) {
				if (NULL!=m_listSub[iii]) {
					m_listSub[iii]->IGenerate(_data, _indent+1);
				}
			}
			AddIndent(_data, _indent);
		}
		_data += "</";
		_data += m_value;
		_data += ">\n";
	} else {
		_data += "/>\n";
	}
	return true;
}


bool exml::Element::SubParse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc, bool _mainNode)
{
	EXML_PARSE_ELEMENT(" start subParse ... " << _pos << " " << _filePos);
	for (int32_t iii=_pos; iii<_data.Size(); iii++) {
		_filePos.Check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			DrawElementParsed(_data[iii], _filePos);
		#endif
		exml::filePos tmpPos;
		if (_data[iii] == '<') {
			int32_t white = CountWhiteChar(_data, iii+1, tmpPos);
			if (iii+white+1>=_data.Size()) {
				_filePos+=tmpPos;
				CREATE_ERROR(_doc, _data, _pos, _filePos, "End file with '<' char ==> invalide XML");
				_pos = iii+white;
				return false;
			}
			// Detect type of the element:
			if(_data[iii+white+1] == '>') {
				_filePos+=tmpPos;
				CREATE_ERROR(_doc, _data, _pos, _filePos, "Find '>' with no element in the element...");
				_pos = iii+white+1;
				return false;
			}
			if(_data[iii+white+1] == '?') {
				++tmpPos;
				// TODO : white space ...
				if( false == CheckAvaillable(_data[iii+white+2], true) ) {
					CREATE_ERROR(_doc, _data, _pos, _filePos, "Find unavaillable name in the Declaration node...");
					_pos = iii+white+1;
					return false;
				}
				//EXML_DEBUG("Generate node name : '" << _data[iii+1] << "'");
				int32_t endPosName = iii+white+1;
				// Generate element name ...
				for (int32_t jjj=iii+white+2; jjj<_data.Size(); jjj++) {
					if(true == CheckAvaillable(_data[jjj], false) ) {
						// we find the end ...
						endPosName = jjj;
					} else {
						break;
					}
					tmpPos.Check(_data[jjj]);
				}
				etk::UString tmpname = _data.Extract(iii+white+2, endPosName+1);
				if (true==_caseSensitive) {
					tmpname.Lower();
				}
				// Find declaration balise
				exml::Declaration* declaration = new exml::Declaration(tmpname);
				if (NULL==declaration) {
					CREATE_ERROR(_doc, _data, _pos, _filePos, "Allocation Error...");
					return false;
				}
				_filePos += tmpPos;
				_pos = endPosName+1;
				if (false==declaration->IParse(_data, _pos, _caseSensitive, _filePos, _doc)) {
					delete(declaration);
					return false;
				}
				iii = _pos;
				m_listSub.PushBack(declaration);
				continue;
			}
			if(_data[iii+white+1] == '!') {
				++tmpPos;
				// Find special block element
				if (iii+white+2>=_data.Size()) {
					CREATE_ERROR(_doc, _data, _pos, _filePos, "End file with '<!' chars ==> invalide XML");
					return false;
				}
				if(_data[iii+white+2] == '-') {
					++tmpPos;
					if (iii+white+3>=_data.Size()) {
						CREATE_ERROR(_doc, _data, _pos, _filePos, "End file with '<!-' chars ==> invalide XML");
						return false;
					}
					if(_data[iii+white+3] != '-') {
						CREATE_ERROR(_doc, _data, _pos, _filePos, etk::UString("Element parse with '<!-") + _data[iii+3] + "' chars ==> invalide XML");
						return false;
					}
					++tmpPos;
					// find comment:
					exml::Comment* comment = new exml::Comment();
					if (NULL==comment) {
						CREATE_ERROR(_doc, _data, _pos, _filePos, "Allocation error ...");
						return false;
					}
					_pos = iii+white+4;
					_filePos += tmpPos;
					if (false==comment->IParse(_data, _pos, _caseSensitive, _filePos, _doc)) {
						delete(comment);
						return false;
					}
					iii = _pos;
					m_listSub.PushBack(comment);
				} else if (_data[iii+white+2] == '[') {
					++tmpPos;
					if (iii+white+8>=_data.Size()) {
						CREATE_ERROR(_doc, _data, _pos, _filePos, "End file with '<![' chars ==> invalide XML");
						return false;
					}
					if(    _data[iii+white+3] != 'C'
					    || _data[iii+white+4] != 'D'
					    || _data[iii+white+5] != 'A'
					    || _data[iii+white+6] != 'T'
					    || _data[iii+white+7] != 'A'
					    || _data[iii+white+8] != '[') {
						CREATE_ERROR(_doc, _data, _pos, _filePos, etk::UString("Element parse with '<![") + _data[iii+white+3] + _data[iii+white+4] + _data[iii+white+5] + _data[iii+white+6] + _data[iii+white+7] + _data[iii+white+8] + "' chars ==> invalide XML");
						return false;
					}
					tmpPos+=6;
					// find text:
					exml::TextCDATA* text = new exml::TextCDATA();
					if (NULL==text) {
						CREATE_ERROR(_doc, _data, _pos, _filePos, "Allocation error ...");
						return false;
					}
					_pos = iii+9+white;
					_filePos += tmpPos;
					if (false==text->IParse(_data, _pos, _caseSensitive, _filePos, _doc)) {
						delete(text);
						return false;
					}
					iii = _pos;
					m_listSub.PushBack(text);
				} else {
					CREATE_ERROR(_doc, _data, _pos, _filePos, etk::UString("End file with '<!") + _data[iii+white+2] + "' chars ==> invalide XML");
					return false;
				}
				
				continue;
			}
			if(_data[iii+white+1] == '/') {
				++tmpPos;
				//EXML_DEBUG("Generate node name : '" << _data[iii+1] << "'");
				int32_t endPosName = iii+white+1;
				// Generate element name ...
				for (int32_t jjj=iii+white+2; jjj<_data.Size(); jjj++) {
					if(true == CheckAvaillable(_data[jjj], false) ) {
						// we find the end ...
						endPosName = jjj;
					} else {
						break;
					}
					tmpPos.Check(_data[jjj]);
				}
				etk::UString tmpname = _data.Extract(iii+white+2, endPosName+1);
				if (true==_caseSensitive) {
					tmpname.Lower();
				}
				if( tmpname == m_value) {
					// find end of node :
					// find > element ... 
					for (int32_t jjj=endPosName+1; jjj<_data.Size(); jjj++) {
						#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
							DrawElementParsed(_data[jjj], _filePos);
						#endif
						if (true==tmpPos.Check(_data[jjj])) {
							continue;
						}
						if(_data[jjj] == '>') {
							_pos = jjj;
							_filePos += tmpPos;
							return true;
						} else if(    _data[jjj] != '\r'
						           && _data[jjj] != ' '
						           && _data[jjj] != '\t') {
							_filePos += tmpPos;
							CREATE_ERROR(_doc, _data, jjj, _filePos, etk::UString("End node error : have data inside end node other than [ \\n\\t\\r] ") + m_value + "'");
							return false;
						}
					}
				} else {
					CREATE_ERROR(_doc, _data, _pos, _filePos, etk::UString("End node error : '") + tmpname + "' != '" + m_value + "'");
					return false;
				}
			}
			if (_data[iii+white+1] == '>') {
				// end of something ==> this is really bad
				CREATE_ERROR(_doc, _data, _pos, _filePos, "Find '>' chars ==> invalide XML");
				return false;
			}
			
			if( true == CheckAvaillable(_data[iii+white+1], true) ) {
				++tmpPos;
				//EXML_DEBUG("Generate node name : '" << _data[iii+1] << "'");
				int32_t endPosName = iii+white+1;
				// Generate element name ...
				for (int32_t jjj=iii+white+2; jjj<_data.Size(); jjj++) {
					if(true == CheckAvaillable(_data[jjj], false) ) {
						// we find the end ...
						endPosName = jjj;
					} else {
						break;
					}
					tmpPos.Check(_data[jjj]);
				}
				etk::UString tmpname = _data.Extract(iii+white+1, endPosName+1);
				if (true==_caseSensitive) {
					tmpname.Lower();
				}
				//EXML_INFO("find node named : '" << tmpname << "'");
				// find text:
				exml::Element* element = new exml::Element(tmpname);
				if (NULL==element) {
					CREATE_ERROR(_doc, _data, _pos, _filePos, "Allocation error ...");
					return false;
				}
				_pos = endPosName+1;
				_filePos += tmpPos;
				if (false==element->IParse(_data, _pos, _caseSensitive, _filePos, _doc)) {
					delete(element);
					return false;
				}
				iii = _pos;
				m_listSub.PushBack(element);
				continue;
			}
			_filePos+=tmpPos;
			// here we have an error : 
			CREATE_ERROR(_doc, _data, _pos, _filePos, etk::UString("Find an ununderstanding element : '") + _data[iii+white+1] + "'");
			return false;
		} else {
			if (_data[iii] == '>') {
				CREATE_ERROR(_doc, _data, _pos, _filePos, "Find elemement '>' ==> no reason to be here ...");
				return false;
			}
			// might to be data text ...
			if(    _data[iii] == '\n'
			    || _data[iii] == ' '
			    || _data[iii] == '\t'
			    || _data[iii] == '\r') {
				// empty spaces ==> nothing to do ....
			} else {
				// find data ==> parse it...
				exml::Text* text = new exml::Text();
				if (NULL==text) {
					CREATE_ERROR(_doc, _data, _pos, _filePos, "Allocation error ...");
					return false;
				}
				_pos = iii;
				_filePos += tmpPos;
				if (false==text->IParse(_data, _pos, _caseSensitive, _filePos, _doc)) {
					delete(text);
					return false;
				}
				iii = _pos;
				m_listSub.PushBack(text);
			}
		}
	}
	if (_mainNode == true) {
		return true;
	}
	CREATE_ERROR(_doc, _data, _pos, _filePos, etk::UString("Did not find end of the exml::Element : '") + m_value + "'");
	return false;
}

bool exml::Element::IParse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc)
{
	EXML_PARSE_ELEMENT("start parse : 'element' named='" << m_value << "'");
	// note : When start parsing the upper element must have set the value of the element and set the position after this one
	m_pos=_filePos;
	// find a normal node ...
	for (int32_t iii=_pos; iii<_data.Size(); iii++) {
		_filePos.Check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			DrawElementParsed(_data[iii], _filePos);
		#endif
		if(_data[iii] == '>') {
			// we find the end ...
			_pos = iii+1;
			return exml::Element::SubParse(_data, _pos, _caseSensitive, _filePos, _doc, false);
		}
		if (_data[iii] == '/') {
			// standalone node or error...
			if (iii+1>=_data.Size()) {
				CREATE_ERROR(_doc, _data, _pos, _filePos, "Find end of files ... ==> bad case");
				return false;
			}
			// TODO : Can have white spaces ....
			if (_data[iii+1] == '>') {
				_pos = iii+1;
				return true;
			}
			// error
			CREATE_ERROR(_doc, _data, _pos, _filePos, "Find / without > char ...");
			return false;
		}
		if (true == CheckAvaillable(_data[iii], true)) {
			// we find an attibute ==> create a new and parse it :
			exml::Attribute* attribute = new exml::Attribute();
			if (NULL==attribute) {
				CREATE_ERROR(_doc, _data, _pos, _filePos, "Allocation error ...");
				return false;
			}
			_pos = iii;
			if (false==attribute->IParse(_data, _pos, _caseSensitive, _filePos, _doc)) {
				delete(attribute);
				return false;
			}
			iii = _pos;
			m_listAttribute.PushBack(attribute);
			continue;
		}
		if (false==_data[iii].IsWhiteChar()) {
			CREATE_ERROR(_doc, _data, iii, _filePos, etk::UString("Find an unknow element : '") + _data[iii] + "'");
			return false;
		}
	}
	CREATE_ERROR(_doc, _data, _pos, _filePos, etk::UString("Unexpecting end of parsing exml::Element : '") + m_value + "' ==> check if the '/>' is set or the end of element");
	return false;
}

void exml::Element::Clear(void)
{
	exml::AttributeList::Clear();
	for (int32_t iii=0; iii<m_listSub.Size(); iii++) {
		if (NULL!=m_listSub[iii]) {
			delete(m_listSub[iii]);
			m_listSub[iii]=NULL;
		}
	}
	m_listSub.Clear();
}



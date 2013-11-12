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
#define __class__ "Element"


exml::Element::~Element(void) {
	for (int32_t iii=0; iii<m_listSub.size(); iii++) {
		if (NULL!=m_listSub[iii]) {
			delete(m_listSub[iii]);
			m_listSub[iii]=NULL;
		}
	}
	m_listSub.clear();
}

enum exml::nodeType exml::Element::getType(int32_t _id) {
	exml::Node* tmpp = getNode(_id);
	if (NULL == tmpp) {
		return exml::typeUnknow;
	}
	return tmpp->getType();
}
const enum exml::nodeType exml::Element::getType(int32_t _id) const {
	const exml::Node* tmpp = getNode(_id);
	if (NULL == tmpp) {
		return exml::typeUnknow;
	}
	return tmpp->getType();
}

exml::Node* exml::Element::getNode(int32_t _id) {
	if (_id <0 || _id>m_listSub.size()) {
		return NULL;
	}
	return m_listSub[_id];
}

const exml::Node* exml::Element::getNode(int32_t _id) const {
	if (_id <0 || _id>m_listSub.size()) {
		return NULL;
	}
	return m_listSub[_id];
}


exml::Element* exml::Element::getElement(int32_t _id) {
	exml::Node* tmpp = getNode(_id);
	if (NULL == tmpp) {
		return NULL;
	}
	return tmpp->toElement();
}

const exml::Element* exml::Element::getElement(int32_t _id) const {
	const exml::Node* tmpp = getNode(_id);
	if (NULL == tmpp) {
		return NULL;
	}
	return tmpp->toElement();
}

exml::Element* exml::Element::getNamed(const std::string& _name) {
	if (_name.size() == 0) {
		return NULL;
	}
	for (int32_t iii=0; iii<m_listSub.size(); iii++) {
		if(    NULL != m_listSub[iii]
		    && m_listSub[iii]->getType() == exml::typeElement
		    && m_listSub[iii]->getValue() == _name) {
			if (NULL == m_listSub[iii]) {
				return NULL;
			}
			return m_listSub[iii]->toElement();
		}
	}
	return NULL;
}
exml::Element* exml::Element::getNamed(const std::u32string& _name) {
	return getNamed(to_u8string(_name));
}

const exml::Element* exml::Element::getNamed(const std::string& _name) const {
	if (_name.size() == 0) {
		return NULL;
	}
	for (int32_t iii=0; iii<m_listSub.size(); iii++) {
		if(    NULL != m_listSub[iii]
		    && m_listSub[iii]->getType() == exml::typeElement
		    && m_listSub[iii]->getValue() == _name) {
			if (NULL == m_listSub[iii]) {
				return NULL;
			}
			return m_listSub[iii]->toElement();
		}
	}
	return NULL;
}
const exml::Element* exml::Element::getNamed(const std::u32string& _name) const {
	return getNamed(to_u8string(_name));
}

void exml::Element::append(exml::Node* _node) {
	if (_node == NULL) {
		EXML_ERROR("Try to set an empty node");
		return;
	}
	if (_node->getType() == exml::typeAttribute) {
		appendAttribute(_node->toAttribute());
		return;
	}
	for (int32_t iii=0; iii<m_listSub.size(); iii++) {
		if (m_listSub[iii] == _node) {
			EXML_ERROR("Try to add a node that is already added before !!!");
			return;
		}
	}
	m_listSub.push_back(_node);
}

std::string exml::Element::getText(void) {
	// TODO : add more capabilities ...
	std::string res;
	for (int32_t iii=0; iii<m_listSub.size(); iii++) {
		if (NULL!=m_listSub[iii]) {
			m_listSub[iii]->iGenerate(res, 0);
		}
	}
	return res;
}

bool exml::Element::iGenerate(std::string& _data, int32_t _indent) const {
	addIndent(_data, _indent);
	_data += "<";
	_data += m_value;
	exml::AttributeList::iGenerate(_data, _indent);
	
	if (m_listSub.size()>0) {
		if(    m_listSub.size() == 1
		    && m_listSub[0] != NULL
		    && m_listSub[0]->getType() == exml::typeText
		    && static_cast<exml::Text*>(m_listSub[0])->countLines() == 1) {
			_data += ">";
			m_listSub[0]->iGenerate(_data,0);
		} else {
			_data += ">\n";
			
			for (int32_t iii=0; iii<m_listSub.size(); iii++) {
				if (NULL!=m_listSub[iii]) {
					m_listSub[iii]->iGenerate(_data, _indent+1);
				}
			}
			addIndent(_data, _indent);
		}
		_data += "</";
		_data += m_value;
		_data += ">\n";
	} else {
		_data += "/>\n";
	}
	return true;
}


bool exml::Element::subParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc, bool _mainNode) {
	EXML_PARSE_ELEMENT(" start subParse ... " << _pos << " " << _filePos);
	for (int32_t iii=_pos; iii<_data.size(); iii++) {
		_filePos.check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			drawElementParsed(_data[iii], _filePos);
		#endif
		exml::filePos tmpPos;
		if (_data[iii] == '<') {
			int32_t white = countWhiteChar(_data, iii+1, tmpPos);
			if (iii+white+1>=_data.size()) {
				_filePos+=tmpPos;
				CREATE_ERROR(_doc, _data, _pos, _filePos, "End file with '<' char  == > invalide XML");
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
				if( false == checkAvaillable(_data[iii+white+2], true) ) {
					CREATE_ERROR(_doc, _data, _pos, _filePos, "Find unavaillable name in the Declaration node...");
					_pos = iii+white+1;
					return false;
				}
				//EXML_DEBUG("Generate node name : '" << _data[iii+1] << "'");
				int32_t endPosName = iii+white+1;
				// generate element name ...
				for (int32_t jjj=iii+white+2; jjj<_data.size(); jjj++) {
					if(true == checkAvaillable(_data[jjj], false) ) {
						// we find the end ...
						endPosName = jjj;
					} else {
						break;
					}
					tmpPos.check(_data[jjj]);
				}
				std::string tmpname = std::string(_data, iii+white+2, endPosName+1);
				if (true == _caseSensitive) {
					tmpname = to_lower(tmpname);
				}
				// Find declaration balise
				exml::Declaration* declaration = new exml::Declaration(tmpname);
				if (NULL == declaration) {
					CREATE_ERROR(_doc, _data, _pos, _filePos, "Allocation Error...");
					return false;
				}
				_filePos += tmpPos;
				_pos = endPosName+1;
				if (false == declaration->iParse(_data, _pos, _caseSensitive, _filePos, _doc)) {
					delete(declaration);
					return false;
				}
				iii = _pos;
				m_listSub.push_back(declaration);
				continue;
			}
			if(_data[iii+white+1] == '!') {
				++tmpPos;
				// Find special block element
				if (iii+white+2>=_data.size()) {
					CREATE_ERROR(_doc, _data, _pos, _filePos, "End file with '<!' chars  == > invalide XML");
					return false;
				}
				if(_data[iii+white+2] == '-') {
					++tmpPos;
					if (iii+white+3>=_data.size()) {
						CREATE_ERROR(_doc, _data, _pos, _filePos, "End file with '<!-' chars  == > invalide XML");
						return false;
					}
					if(_data[iii+white+3] != '-') {
						CREATE_ERROR(_doc, _data, _pos, _filePos, std::string("Element parse with '<!-") + _data[iii+3] + "' chars  == > invalide XML");
						return false;
					}
					++tmpPos;
					// find comment:
					exml::Comment* comment = new exml::Comment();
					if (NULL == comment) {
						CREATE_ERROR(_doc, _data, _pos, _filePos, "Allocation error ...");
						return false;
					}
					_pos = iii+white+4;
					_filePos += tmpPos;
					if (false == comment->iParse(_data, _pos, _caseSensitive, _filePos, _doc)) {
						delete(comment);
						return false;
					}
					iii = _pos;
					m_listSub.push_back(comment);
				} else if (_data[iii+white+2] == '[') {
					++tmpPos;
					if (iii+white+8>=_data.size()) {
						CREATE_ERROR(_doc, _data, _pos, _filePos, "End file with '<![' chars  == > invalide XML");
						return false;
					}
					if(    _data[iii+white+3] != 'C'
					    || _data[iii+white+4] != 'D'
					    || _data[iii+white+5] != 'A'
					    || _data[iii+white+6] != 'T'
					    || _data[iii+white+7] != 'A'
					    || _data[iii+white+8] != '[') {
						CREATE_ERROR(_doc, _data, _pos, _filePos, std::string("Element parse with '<![") + _data[iii+white+3] + _data[iii+white+4] + _data[iii+white+5] + _data[iii+white+6] + _data[iii+white+7] + _data[iii+white+8] + "' chars  == > invalide XML");
						return false;
					}
					tmpPos+=6;
					// find text:
					exml::TextCDATA* text = new exml::TextCDATA();
					if (NULL == text) {
						CREATE_ERROR(_doc, _data, _pos, _filePos, "Allocation error ...");
						return false;
					}
					_pos = iii+9+white;
					_filePos += tmpPos;
					if (false == text->iParse(_data, _pos, _caseSensitive, _filePos, _doc)) {
						delete(text);
						return false;
					}
					iii = _pos;
					m_listSub.push_back(text);
				} else {
					CREATE_ERROR(_doc, _data, _pos, _filePos, std::string("End file with '<!") + _data[iii+white+2] + "' chars  == > invalide XML");
					return false;
				}
				
				continue;
			}
			if(_data[iii+white+1] == '/') {
				++tmpPos;
				//EXML_DEBUG("Generate node name : '" << _data[iii+1] << "'");
				int32_t endPosName = iii+white+1;
				// generate element name ...
				for (int32_t jjj=iii+white+2; jjj<_data.size(); jjj++) {
					if(true == checkAvaillable(_data[jjj], false) ) {
						// we find the end ...
						endPosName = jjj;
					} else {
						break;
					}
					tmpPos.check(_data[jjj]);
				}
				std::string tmpname = std::string(_data, iii+white+2, endPosName+1);
				if (true == _caseSensitive) {
					tmpname = to_lower(tmpname);
				}
				if( tmpname == m_value) {
					// find end of node :
					// find > element ... 
					for (int32_t jjj=endPosName+1; jjj<_data.size(); jjj++) {
						#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
							drawElementParsed(_data[jjj], _filePos);
						#endif
						if (true == tmpPos.check(_data[jjj])) {
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
							CREATE_ERROR(_doc, _data, jjj, _filePos, std::string("End node error : have data inside end node other than [ \\n\\t\\r] ") + m_value + "'");
							return false;
						}
					}
				} else {
					CREATE_ERROR(_doc, _data, _pos, _filePos, std::string("End node error : '") + tmpname + "' != '" + m_value + "'");
					return false;
				}
			}
			if (_data[iii+white+1] == '>') {
				// end of something  == > this is really bad
				CREATE_ERROR(_doc, _data, _pos, _filePos, "Find '>' chars  == > invalide XML");
				return false;
			}
			
			if( true == checkAvaillable(_data[iii+white+1], true) ) {
				++tmpPos;
				//EXML_DEBUG("Generate node name : '" << _data[iii+1] << "'");
				int32_t endPosName = iii+white+1;
				// generate element name ...
				for (int32_t jjj=iii+white+2; jjj<_data.size(); jjj++) {
					if(true == checkAvaillable(_data[jjj], false) ) {
						// we find the end ...
						endPosName = jjj;
					} else {
						break;
					}
					tmpPos.check(_data[jjj]);
				}
				std::string tmpname = std::string(_data, iii+white+1, endPosName+1);
				if (true == _caseSensitive) {
					to_lower(tmpname);
				}
				//EXML_INFO("find node named : '" << tmpname << "'");
				// find text:
				exml::Element* element = new exml::Element(tmpname);
				if (NULL == element) {
					CREATE_ERROR(_doc, _data, _pos, _filePos, "Allocation error ...");
					return false;
				}
				_pos = endPosName+1;
				_filePos += tmpPos;
				if (false == element->iParse(_data, _pos, _caseSensitive, _filePos, _doc)) {
					delete(element);
					return false;
				}
				iii = _pos;
				m_listSub.push_back(element);
				continue;
			}
			_filePos+=tmpPos;
			// here we have an error : 
			CREATE_ERROR(_doc, _data, _pos, _filePos, std::string("Find an ununderstanding element : '") + _data[iii+white+1] + "'");
			return false;
		} else {
			if (_data[iii] == '>') {
				CREATE_ERROR(_doc, _data, _pos, _filePos, "Find elemement '>'  == > no reason to be here ...");
				return false;
			}
			// might to be data text ...
			if(    _data[iii] == '\n'
			    || _data[iii] == ' '
			    || _data[iii] == '\t'
			    || _data[iii] == '\r') {
				// empty spaces  == > nothing to do ....
			} else {
				// find data  == > parse it...
				exml::Text* text = new exml::Text();
				if (NULL == text) {
					CREATE_ERROR(_doc, _data, _pos, _filePos, "Allocation error ...");
					return false;
				}
				_pos = iii;
				_filePos += tmpPos;
				if (false == text->iParse(_data, _pos, _caseSensitive, _filePos, _doc)) {
					delete(text);
					return false;
				}
				iii = _pos;
				m_listSub.push_back(text);
			}
		}
	}
	if (_mainNode == true) {
		return true;
	}
	CREATE_ERROR(_doc, _data, _pos, _filePos, std::string("Did not find end of the exml::Element : '") + m_value + "'");
	return false;
}

bool exml::Element::iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc) {
	EXML_PARSE_ELEMENT("start parse : 'element' named='" << m_value << "'");
	// note : When start parsing the upper element must have set the value of the element and set the position after this one
	m_pos=_filePos;
	// find a normal node ...
	for (int32_t iii=_pos; iii<_data.size(); iii++) {
		_filePos.check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
		 drawElementParsed(_data[iii], _filePos);
		#endif
		if(_data[iii] == '>') {
			// we find the end ...
			_pos = iii+1;
			return exml::Element::subParse(_data, _pos, _caseSensitive, _filePos, _doc, false);
		}
		if (_data[iii] == '/') {
			// standalone node or error...
			if (iii+1>=_data.size()) {
				CREATE_ERROR(_doc, _data, _pos, _filePos, "Find end of files ...  == > bad case");
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
		if (true == checkAvaillable(_data[iii], true)) {
			// we find an attibute  == > create a new and parse it :
			exml::Attribute* attribute = new exml::Attribute();
			if (NULL == attribute) {
				CREATE_ERROR(_doc, _data, _pos, _filePos, "Allocation error ...");
				return false;
			}
			_pos = iii;
			if (false == attribute->iParse(_data, _pos, _caseSensitive, _filePos, _doc)) {
				delete(attribute);
				return false;
			}
			iii = _pos;
			m_listAttribute.push_back(attribute);
			continue;
		}
		if (false == etk::isWhiteChar(_data[iii])) {
			CREATE_ERROR(_doc, _data, iii, _filePos, std::string("Find an unknow element : '") + _data[iii] + "'");
			return false;
		}
	}
	CREATE_ERROR(_doc, _data, _pos, _filePos, std::string("Unexpecting end of parsing exml::Element : '") + m_value + "'  == > check if the '/>' is set or the end of element");
	return false;
}

void exml::Element::clear(void) {
	exml::AttributeList::clear();
	for (int32_t iii=0; iii<m_listSub.size(); iii++) {
		if (NULL!=m_listSub[iii]) {
			delete(m_listSub[iii]);
			m_listSub[iii]=NULL;
		}
	}
	m_listSub.clear();
}



/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <exml/internal/Element.h>
#include <exml/debug.h>
#include <exml/internal/Text.h>
#include <exml/internal/Comment.h>
#include <exml/internal/Attribute.h>
#include <exml/internal/Declaration.h>
#include <exml/internal/Document.h>

static bool isWhiteChar(char32_t _val) {
	if(    _val == ' '
	    || _val == '\t'
	    || _val == '\n'
	    || _val == '\r') {
		return true;
	}
	return false;
}

ememory::SharedPtr<exml::internal::Element> exml::internal::Element::create(const std::string& _value) {
	return ememory::SharedPtr<exml::internal::Element>(new exml::internal::Element(_value));
}

enum exml::nodeType exml::internal::Element::getType(int32_t _id) const {
	ememory::SharedPtr<const exml::internal::Node> tmpp = getNode(_id);
	if (tmpp == nullptr) {
		return exml::nodeType::unknow;
	}
	return tmpp->getType();
}

ememory::SharedPtr<exml::internal::Node> exml::internal::Element::getNode(int32_t _id) {
	if (    _id <0
	     || (size_t)_id>=m_listSub.size()) {
		return nullptr;
	}
	return m_listSub[_id];
}

const ememory::SharedPtr<exml::internal::Node> exml::internal::Element::getNode(int32_t _id) const {
	if (    _id <0
	     || (size_t)_id>=m_listSub.size()) {
		return nullptr;
	}
	return m_listSub[_id];
}


ememory::SharedPtr<exml::internal::Element> exml::internal::Element::getElement(int32_t _id) {
	ememory::SharedPtr<exml::internal::Node> tmpp = getNode(_id);
	if (tmpp == nullptr) {
		return nullptr;
	}
	return tmpp->toElement();
}

const ememory::SharedPtr<exml::internal::Element> exml::internal::Element::getElement(int32_t _id) const {
	const ememory::SharedPtr<exml::internal::Node> tmpp = getNode(_id);
	if (tmpp == nullptr) {
		return nullptr;
	}
	return tmpp->toElement();
}

ememory::SharedPtr<exml::internal::Element> exml::internal::Element::getNamed(const std::string& _name) {
	if (_name.size() == 0) {
		return nullptr;
	}
	for (size_t iii=0; iii<m_listSub.size(); iii++) {
		if(    m_listSub[iii] != nullptr
		    && m_listSub[iii]->getType() == exml::nodeType::element
		    && m_listSub[iii]->getValue() == _name) {
			if (m_listSub[iii] == nullptr) {
				return nullptr;
			}
			return m_listSub[iii]->toElement();
		}
	}
	return nullptr;
}

const ememory::SharedPtr<exml::internal::Element> exml::internal::Element::getNamed(const std::string& _name) const {
	if (_name.size() == 0) {
		return nullptr;
	}
	for (size_t iii=0; iii<m_listSub.size(); iii++) {
		if(    m_listSub[iii] != nullptr
		    && m_listSub[iii]->getType() == exml::nodeType::element
		    && m_listSub[iii]->getValue() == _name) {
			if (m_listSub[iii] == nullptr) {
				return nullptr;
			}
			return m_listSub[iii]->toElement();
		}
	}
	return nullptr;
}

void exml::internal::Element::append(const ememory::SharedPtr<exml::internal::Node>& _node) {
	if (_node == nullptr) {
		EXML_ERROR("Try to set an empty node");
		return;
	}
	if (_node->getType() == exml::nodeType::attribute) {
		appendAttribute(_node->toAttribute());
		return;
	}
	for (size_t iii=0; iii<m_listSub.size(); iii++) {
		if (m_listSub[iii] == _node) {
			EXML_ERROR("Try to add a node that is already added before !!!");
			return;
		}
	}
	m_listSub.push_back(_node);
}

void exml::internal::Element::remove(const std::string& _nodeName) {
	if (_nodeName == "") {
		return;
	}
	auto it = m_listSub.begin();
	while (it != m_listSub.end()) {
		if (*it == nullptr) {
			it = m_listSub.erase(it);
		} else if ((*it)->getValue() == _nodeName) {
			it = m_listSub.erase(it);
		} else {
			++it;
		}
	}
}

std::string exml::internal::Element::getText() const {
	std::string res;
	if (m_listSub.size() == 1) {
		if (m_listSub[0]->getType() == nodeType::text) {
			res = m_listSub[0]->getValue();
		} else {
			m_listSub[0]->iGenerate(res, 0);
		}
	} else {
		for (size_t iii=0; iii<m_listSub.size(); iii++) {
			if (m_listSub[iii] != nullptr) {
				m_listSub[iii]->iGenerate(res, 0);
			}
		}
	}
	return res;
}

bool exml::internal::Element::iGenerate(std::string& _data, int32_t _indent) const {
	addIndent(_data, _indent);
	_data += "<";
	_data += m_value;
	exml::internal::AttributeList::iGenerate(_data, _indent);
	
	if (m_listSub.size()>0) {
		if(    m_listSub.size() == 1
		    && m_listSub[0] != nullptr
		    && m_listSub[0]->getType() == exml::nodeType::text
		    && ememory::dynamicPointerCast<exml::internal::Text>(m_listSub[0])->countLines() == 1) {
			_data += ">";
			m_listSub[0]->iGenerate(_data,0);
			EXML_VERBOSE(" generate : '" << _data << "'");
		} else {
			_data += ">\n";
			
			for (size_t iii=0; iii<m_listSub.size(); iii++) {
				if (m_listSub[iii] != nullptr) {
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


bool exml::internal::Element::subParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::FilePos& _filePos, exml::internal::Document& _doc, bool _mainNode) {
	EXML_PARSE_ELEMENT(" start subParse ... " << _pos << " " << _filePos);
	for (size_t iii=_pos; iii<_data.size(); iii++) {
		_filePos.check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			drawElementParsed(_data[iii], _filePos);
		#endif
		exml::FilePos tmpPos;
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
				if(checkAvaillable(_data[iii+white+2], true) == false) {
					CREATE_ERROR(_doc, _data, _pos, _filePos, "Find unavaillable name in the Declaration node...");
					_pos = iii+white+1;
					return false;
				}
				//EXML_DEBUG("Generate node name : '" << _data[iii+1] << "'");
				size_t endPosName = iii+white+1;
				// generate element name ...
				for (size_t jjj=iii+white+2; jjj<_data.size(); jjj++) {
					if(checkAvaillable(_data[jjj], false) == true) {
						// we find the end ...
						endPosName = jjj;
					} else {
						break;
					}
					tmpPos.check(_data[jjj]);
				}
				std::string tmpname = std::string(_data, iii+white+2, endPosName+1-(iii+white+2));
				if (_caseSensitive == true) {
					tmpname = etk::tolower(tmpname);
				}
				// Find declaration balise
				ememory::SharedPtr<exml::internal::Declaration> declaration = exml::internal::Declaration::create(tmpname);
				if (declaration == nullptr) {
					CREATE_ERROR(_doc, _data, _pos, _filePos, "Allocation Error...");
					return false;
				}
				_filePos += tmpPos;
				_pos = endPosName+1;
				if (declaration->iParse(_data, _pos, _caseSensitive, _filePos, _doc) == false) {
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
					ememory::SharedPtr<exml::internal::Comment> comment = exml::internal::Comment::create();
					if (comment == nullptr) {
						CREATE_ERROR(_doc, _data, _pos, _filePos, "Allocation error ...");
						return false;
					}
					_pos = iii+white+4;
					_filePos += tmpPos;
					if (comment->iParse(_data, _pos, _caseSensitive, _filePos, _doc) == false) {
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
					ememory::SharedPtr<exml::internal::TextCDATA> text = exml::internal::TextCDATA::create();
					if (text == nullptr) {
						CREATE_ERROR(_doc, _data, _pos, _filePos, "Allocation error ...");
						return false;
					}
					_pos = iii+9+white;
					_filePos += tmpPos;
					if (text->iParse(_data, _pos, _caseSensitive, _filePos, _doc) == false) {
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
				size_t endPosName = iii+white+1;
				// generate element name ...
				for (size_t jjj=iii+white+2; jjj<_data.size(); jjj++) {
					if(checkAvaillable(_data[jjj], false) == true) {
						// we find the end ...
						endPosName = jjj;
					} else {
						break;
					}
					tmpPos.check(_data[jjj]);
				}
				std::string tmpname = std::string(_data, iii+white+2, endPosName+1-(iii+white+2));
				if (_caseSensitive == true) {
					tmpname = etk::tolower(tmpname);
				}
				if( tmpname == m_value) {
					// find end of node :
					// find > element ... 
					for (size_t jjj=endPosName+1; jjj<_data.size(); jjj++) {
						#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
							drawElementParsed(_data[jjj], _filePos);
						#endif
						if (tmpPos.check(_data[jjj]) == true) {
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
			
			if (checkAvaillable(_data[iii+white+1], true) == true) {
				++tmpPos;
				//EXML_DEBUG("Generate node name : '" << _data[iii+1] << "'");
				size_t endPosName = iii+white+1;
				// generate element name ...
				for (size_t jjj=iii+white+2; jjj<_data.size(); jjj++) {
					if(checkAvaillable(_data[jjj], false) == true) {
						// we find the end ...
						endPosName = jjj;
					} else {
						break;
					}
					tmpPos.check(_data[jjj]);
				}
				std::string tmpname = std::string(_data, iii+white+1, endPosName+1-(iii+white+1));
				if (_caseSensitive == true) {
					etk::tolower(tmpname);
				}
				//EXML_INFO("find node named : '" << tmpname << "'");
				// find text:
				ememory::SharedPtr<exml::internal::Element> element = exml::internal::Element::create(tmpname);
				if (element == nullptr) {
					CREATE_ERROR(_doc, _data, _pos, _filePos, "Allocation error ...");
					return false;
				}
				_pos = endPosName+1;
				_filePos += tmpPos;
				if (element->iParse(_data, _pos, _caseSensitive, _filePos, _doc) == false) {
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
				ememory::SharedPtr<exml::internal::Text> text = exml::internal::Text::create();
				if (text == nullptr) {
					CREATE_ERROR(_doc, _data, _pos, _filePos, "Allocation error ...");
					return false;
				}
				_pos = iii;
				_filePos += tmpPos;
				if (text->iParse(_data, _pos, _caseSensitive, _filePos, _doc) == false) {
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
	CREATE_ERROR(_doc, _data, _pos, _filePos, std::string("Did not find end of the exml::internal::Element : '") + m_value + "'");
	return false;
}

bool exml::internal::Element::iParse(const std::string& _data,
                                     int32_t& _pos,
                                     bool _caseSensitive,
                                     exml::FilePos& _filePos,
                                     exml::internal::Document& _doc) {
	EXML_PARSE_ELEMENT("start parse : 'element' named='" << m_value << "'");
	// note : When start parsing the upper element must have set the value of the element and set the position after this one
	m_pos=_filePos;
	// find a normal node ...
	for (size_t iii=_pos; iii<_data.size(); iii++) {
		_filePos.check(_data[iii]);
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
		 drawElementParsed(_data[iii], _filePos);
		#endif
		if(_data[iii] == '>') {
			// we find the end ...
			_pos = iii+1;
			return exml::internal::Element::subParse(_data, _pos, _caseSensitive, _filePos, _doc, false);
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
		if (checkAvaillable(_data[iii], true) == true) {
			// we find an attibute  == > create a new and parse it :
			ememory::SharedPtr<exml::internal::Attribute> attribute = exml::internal::Attribute::create();
			if (attribute == nullptr) {
				CREATE_ERROR(_doc, _data, _pos, _filePos, "Allocation error ...");
				return false;
			}
			_pos = iii;
			if (attribute->iParse(_data, _pos, _caseSensitive, _filePos, _doc) == false) {
				return false;
			}
			iii = _pos;
			m_listAttribute.push_back(attribute);
			continue;
		}
		if (isWhiteChar(_data[iii]) == false) {
			CREATE_ERROR(_doc, _data, iii, _filePos, std::string("Find an unknow element : '") + _data[iii] + "'");
			return false;
		}
	}
	CREATE_ERROR(_doc, _data, _pos, _filePos, std::string("Unexpecting end of parsing exml::internal::Element : '") + m_value + "'  == > check if the '/>' is set or the end of element");
	return false;
}

void exml::internal::Element::clear() {
	exml::internal::AttributeList::clear();
	m_listSub.clear();
}


ememory::SharedPtr<exml::internal::Element> exml::internal::Element::toElement() {
	return ememory::staticPointerCast<exml::internal::Element>(sharedFromThis());
}

const ememory::SharedPtr<exml::internal::Element> exml::internal::Element::toElement() const {
	return ememory::staticPointerCast<exml::internal::Element>(sharedFromThis());
}


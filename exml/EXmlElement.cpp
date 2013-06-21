/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <exml/EXmlElement.h>
#include <exml/debug.h>
#include <exml/EXmlText.h>
#include <exml/EXmlComment.h>
#include <exml/EXmlAttribute.h>
#include <exml/EXmlDeclaration.h>


exml::EXmlNode* exml::EXmlElement::GetSub(int32_t _id)
{
	if (_id <0 || _id>m_listSub.Size()) {
		return NULL;
	}
	return m_listSub[_id];
}

void exml::EXmlElement::AppendSub(exml::EXmlNode* _node)
{
	if (_node == NULL) {
		EXML_ERROR("Try to set an empty node");
		return;
	}
	for (int32_t iii=0; iii<m_listSub.Size(); iii++) {
		if (m_listSub[iii] == _node) {
			EXML_ERROR("Try to add a node that is already added befor !!!");
			return;
		}
	}
	m_listSub.PushBack(_node);
}

exml::EXmlNode* exml::EXmlElement::GetNode(const etk::UString& _name)
{
	if (_name.Size()==0) {
		return NULL;
	}
	for (int32_t iii=0; iii<m_listSub.Size(); iii++) {
		if(    NULL != m_listSub[iii]
		    && m_listSub[iii]->GetType() == exml::typeElement
		    && m_listSub[iii]->GetValue() == _name) {
			return m_listSub[iii];
		}
	}
	return NULL;
}

exml::EXmlAttribute* exml::EXmlElement::GetAttribute(int32_t _id)
{
	if (_id <0 || _id>m_listAttribute.Size()) {
		return NULL;
	}
	return m_listAttribute[_id];
}
void exml::EXmlElement::AppendAttribute(exml::EXmlAttribute* _node)
{
	if (_node == NULL) {
		EXML_ERROR("Try to set an empty node");
		return;
	}
	for (int32_t iii=0; iii<m_listAttribute.Size(); iii++) {
		if (m_listAttribute[iii] == _node) {
			EXML_ERROR("Try to add a node that is already added befor !!!");
			return;
		}
	}
	m_listAttribute.PushBack(_node);
}

const etk::UString& exml::EXmlElement::GetAttribute(const etk::UString& _name)
{
	static const etk::Ustring errorReturn("");
	if (_name.Size()==0) {
		return errorReturn;
	}
	for (int32_t iii=0; iii<m_listAttribute.Size(); iii++) {
		if(    NULL != m_listAttribute[iii]
		    && m_listAttribute[iii]->GetName() == _name) {
			return m_listAttribute[iii]->GetValue();
		}
	}
	return errorReturn;
}

bool exml::EXmlElement::Generate(etk::UString& _data, int32_t _indent)
{
	AddIndent(_data, _indent);
	_data += "<";
	_data += m_name;
	for (int32_t iii=0; iii<m_listAttribute.Size(); iii++) {
		if (NULL!=m_listAttribute[iii]) {
			m_listAttribute[iii]->Generate(_data, _indent);
		}
	}
	
	if (m_listSub.Size()>0) {
		if(    m_listSub.Size()==1
		    && m_listSub[0] != NULL
		    && m_listSub[0]->GetType() == exml::typeText
		    && static_cast<exml::EXmlText*>(m_listSub[0])->CountLines()==1) {
			_data += ">";
			m_listSub[0]->Generate(_data,0);
		} else {
			_data += ">\n";
			
			for (int32_t iii=0; iii<m_listSub.Size(); iii++) {
				if (NULL!=m_listSub[iii]) {
					m_listSub[iii]->Generate(_data, _indent+1);
				}
			}
			AddIndent(_data, _indent);
		}
		_data += "</";
		_data += m_name;
		_data += ">\n";
	} else {
		_data += "/>\n";
	}
	return true;
}


bool exml::EXmlElement::SubParse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos, bool _mainNode)
{
	EXML_DEBUG(" start subParse ... " << _pos << " " << _filePos);
	for (int32_t iii=_pos; iii<_data.Size(); iii++) {
		_filePos += ivec2(1,0);
		DrawElementParsed(_data[iii], _filePos);
		if (_data[iii] == '<') {
			int32_t white = CountWhiteChar(_data, iii+1);
			if (iii+white+1>=_data.Size()) {
				EXML_ERROR(_filePos << " ==> end file with '<' char ==> invalide XML");
				_pos = iii+white;
				return false;
			}
			// Detect type of the element:
			if(_data[iii+white+1] == '>') {
				EXML_ERROR(_filePos << " find '>' with no element in the element...");
				_pos = iii+white+1;
				return false;
			}
			if(_data[iii+white+1] == '?') {
				// Find declaration balise
				exml::EXmlDeclaration* declaration = new exml::EXmlDeclaration();
				if (NULL==declaration) {
					EXML_ERROR(_filePos << " Allocation error ...");
					return false;
				}
				_pos = iii+white+2;
				_filePos += ivec2(3+white,0);
				if (false==declaration->Parse(_data, _pos, _caseSensitive, _filePos)) {
					delete(declaration);
					return false;
				}
				m_listSub.PushBack(declaration);
				continue;
			}
			if(_data[iii+white+1] == '!') {
				// Find special block element
				if (iii+white+2>=_data.Size()) {
					EXML_ERROR(_filePos << " ==> end file with '<!' chars ==> invalide XML");
					return false;
				}
				if(_data[iii+white+2] == '-') {
					if (iii+white+3>=_data.Size()) {
						EXML_ERROR(_filePos << " ==> end file with '<!-' chars ==> invalide XML");
						return false;
					}
					if(_data[iii+white+3] != '-') {
						EXML_ERROR(_filePos << " ==> element parse with '<!-" << _data[iii+3] << "' chars ==> invalide XML");
						return false;
					}
					// find comment:
					exml::EXmlComment* comment = new exml::EXmlComment();
					if (NULL==comment) {
						EXML_ERROR(_filePos << " Allocation error ...");
						return false;
					}
					_pos = iii+white+4;
					_filePos += ivec2(3+white,0);
					if (false==comment->Parse(_data, _pos, _caseSensitive, _filePos)) {
						delete(comment);
						return false;
					}
					iii = _pos;
					m_listSub.PushBack(comment);
				} else if (_data[iii+white+2] == '[') {
					if (iii+white+8>=_data.Size()) {
						EXML_ERROR(_filePos << " ==> end file with '<![' chars ==> invalide XML");
						return false;
					}
					if(    _data[iii+white+3] != 'C'
					    || _data[iii+white+4] != 'D'
					    || _data[iii+white+5] != 'A'
					    || _data[iii+white+6] != 'T'
					    || _data[iii+white+7] != 'A'
					    || _data[iii+white+8] != '[') {
						EXML_ERROR(_filePos << " ==> element parse with '<![" << _data[iii+white+3] << _data[iii+white+4] << _data[iii+white+5] << _data[iii+white+6] << _data[iii+white+7] << _data[iii+white+8] << "' chars ==> invalide XML");
						return false;
					}
					// find text:
					exml::EXmlTextCDATA* text = new exml::EXmlTextCDATA();
					if (NULL==text) {
						EXML_ERROR(_filePos << " Allocation error ...");
						return false;
					}
					_pos = iii+9+white;
					_filePos += ivec2(8+white,0);
					if (false==text->Parse(_data, _pos, _caseSensitive, _filePos)) {
						delete(text);
						return false;
					}
					iii = _pos;
					m_listSub.PushBack(text);
				} else {
					EXML_ERROR(_filePos << " ==> end file with '<!" << _data[iii+white+2] << "' chars ==> invalide XML");
					return false;
				}
				
				continue;
			}
			if(_data[iii+white+1] == '/') {
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
				}
				etk::UString tmpname = _data.Extract(iii+white+2, endPosName+1);
				if( tmpname == m_value) {
					// find end of node :
					// find > element ... 
					for (int32_t jjj=endPosName+1; jjj<_data.Size(); jjj++) {
						_filePos += ivec2(1,0);
						DrawElementParsed(_data[jjj], _filePos);
						if (_data[jjj] == '\n') {
							_filePos.setValue(0, _filePos.y()+1);
							continue;
						}
						if(_data[jjj] == '>') {
							_pos = jjj;
							return true;
						}
					}
				} else {
					EXML_ERROR(_filePos << " ==> end node error : '" << tmpname << "' != '" << m_name << "'");
					return false;
				}
			}
			if (_data[iii+white+1] == '>') {
				// end of something ==> this is really bad
				EXML_ERROR(_filePos << " ==> find '>' chars ==> invalide XML");
				return false;
			}
			
			if( true == CheckAvaillable(_data[iii+white+1], true) ) {
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
				}
				etk::UString tmpname = _data.Extract(iii+white+1, endPosName+1);
				//EXML_INFO("find node named : '" << tmpname << "'");
				// find text:
				exml::EXmlElement* element = new exml::EXmlElement();
				if (NULL==element) {
					EXML_ERROR(_filePos << " Allocation error ...");
					return false;
				}
				element->SetValue(tmpname);
				_pos = endPosName+1;
				_filePos += ivec2(endPosName,0);
				if (false==element->Parse(_data, _pos, _caseSensitive, _filePos)) {
					delete(element);
					return false;
				}
				iii = _pos;
				m_listSub.PushBack(element);
				
				
				continue;
			}
		} else {
			if (_data[iii] == '>') {
				EXML_ERROR(_filePos << " find elemement '>' ==> no reason to be here ...");
				return false;
			}
			// might to be data text ...
			if (_data[iii] == '\n') {
				_filePos.setValue(1, _filePos.y()+1);
			}else if(    _data[iii] == ' '
			          || _data[iii] == '\t'
			          || _data[iii] == '\r') {
				// empty spaces ==> nothing to do ....
				
			} else {
				// find data ==> parse it...
				exml::EXmlText* text = new exml::EXmlText();
				if (NULL==text) {
					EXML_ERROR(_filePos << " Allocation error ...");
					return false;
				}
				_pos = iii;
				_filePos += ivec2(1,0);
				if (false==text->Parse(_data, _pos, _caseSensitive, _filePos)) {
					delete(text);
					return false;
				}
				iii = _pos;
				m_listSub.PushBack(text);
			}
		}
	}
	return false;
}

bool exml::EXmlElement::Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos)
{
	EXML_DEBUG("start parse : 'element' named='" << m_name << "'");
	// note : When start parsing the upper element must have set the value of the element and set the position after this one
	
	// find a normal node ...
	for (int32_t iii=_pos; iii<_data.Size(); iii++) {
		_filePos += ivec2(1,0);
		if (_data[iii] == '\n') {
			_filePos.setValue(1, _filePos.y()+1);
		}
		EXML_DEBUG("parse : '" << _data[iii] << "'");
		if(_data[iii] == '>') {
			// we find the end ...
			_pos = iii+1;
			return exml::EXmlElement::SubParse(_data, _pos, _caseSensitive, _filePos, false);
		}
		if (_data[iii] == '/') {
			// standalone node or error...
			if (iii+1>=_data.Size()) {
				EXML_ERROR(" find end of files ... ==> bad case");
				return false;
			}
			if (_data[iii+1] == '>') {
				_pos = iii+1;
				return true;
			}
			// error
			EXML_ERROR("find / without > char ...");
			return false;
		}
		if (true == CheckAvaillable(_data[iii], true)) {
			// we find an attibute ==> create a new and parse it :
			exml::EXmlAttribute* attribute = new exml::EXmlAttribute();
			if (NULL==attribute) {
				EXML_ERROR(_filePos << " Allocation error ...");
				return false;
			}
			_pos = iii;
			if (false==attribute->Parse(_data, _pos, _caseSensitive, _filePos)) {
				delete(attribute);
				return false;
			}
			iii = _pos;
			m_listAttribute.PushBack(attribute);
			continue;
		}
		// TODO : Else ==> if not white ==> create an error ...
	}
	
	return false;
}








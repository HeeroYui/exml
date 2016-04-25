/** @file
 * @author Edouard DUPIN
 * @copyright 2011, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <exml/internal/Declaration.h>
#include <exml/debug.h>
#include <exml/internal/Document.h>

/* basic declaration have 3 attributes:
	version
	encoding
	standalone
	<?xml version="1.0" encoding="UTF-8" ?>
*/

ememory::SharedPtr<exml::internal::Declaration> exml::internal::Declaration::create(const std::string& _name) {
	return ememory::SharedPtr<exml::internal::Declaration>(new exml::internal::Declaration(_name));
}

ememory::SharedPtr<exml::internal::DeclarationXML> exml::internal::DeclarationXML::create(const std::string& _version, const std::string& _format, bool _standalone) {
	return ememory::SharedPtr<exml::internal::DeclarationXML>(new exml::internal::DeclarationXML(_version, _format, _standalone));
}

exml::internal::DeclarationXML::DeclarationXML(const std::string& _version, const std::string& _format, bool _standalone) :
  exml::internal::Declaration("xml") {
	if (_version.size()!=0) {
		setAttribute("version", _version);
	}
	if (_format!="UTF-8") {
		setAttribute("encoding", "UTF-8");
	} else {
		EXML_ERROR("Actually does not supported other charset than UTF8");
		setAttribute("encoding", "UTF-8");
	}
	if (_standalone == true) {
		setAttribute("standalone", "true");
	} else {
		setAttribute("standalone", "true");
	}
}

bool exml::internal::Declaration::iGenerate(std::string& _data, int32_t _indent) const {
	addIndent(_data, _indent);
	_data += "<?";
	_data += m_value;
	exml::internal::AttributeList::iGenerate(_data, _indent);
	_data += "?>\n";
	return true;
}

bool exml::internal::Declaration::iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::FilePos& _filePos, exml::internal::Document& _doc) {
	EXML_VERBOSE("start parse : 'declaration' : '" << m_value << "'");
	m_pos = _filePos;
	// search end of the comment :
	for (size_t iii=_pos; iii+1<_data.size(); iii++) {
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
		 drawElementParsed(_data[iii], _filePos);
		#endif
		if (_filePos.check(_data[iii]) == true) {
			continue;
		}
		if(    _data[iii] == '>'
		    || _data[iii] == '<') {
			// an error occured : 
			CREATE_ERROR(_doc, _data, _pos, _filePos, " find '>' or '<'  instead of '?>'");
			return false;
		}
		if(    _data[iii] == '?'
		    && _data[iii+1] == '>') {
			++_filePos;
			// find end of declaration:
			_pos = iii+1;
			return true;
		}
		if (checkAvaillable(_data[iii], true) == true) {
			// we find an attibute  == > create a new and parse it :
			ememory::SharedPtr<exml::internal::Attribute> attribute = exml::internal::Attribute::create();
			if (attribute == nullptr) {
				CREATE_ERROR(_doc, _data, _pos, _filePos, " Allocation error ...");
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
	}
	CREATE_ERROR(_doc, _data, _pos, _filePos, "Text got end of file without finding end node");
	_pos = _data.size();
	return false;
}


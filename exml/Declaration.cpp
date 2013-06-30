/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <exml/Declaration.h>
#include <exml/debug.h>
#include <exml/Document.h>

#undef __class__
#define __class__	"Declaration"

/* basic declaration have 3 attributes:
	version
	encoding
	standalone
	<?xml version="1.0" encoding="UTF-8" ?>
*/

exml::DeclarationXML::DeclarationXML(const etk::UString& _version, unicode::charset_te _format, bool _standalone) :
	exml::Declaration("xml")
{
	if (_version.Size()!=0) {
		SetAttribute("version", _version);
	}
	if (_format!=unicode::EDN_CHARSET_UTF8) {
		SetAttribute("encoding", "UTF-8");
	} else {
		EXML_ERROR("Actually does not supported other charset than UTF8");
		SetAttribute("encoding", "UTF-8");
	}
	if (_standalone==true) {
		SetAttribute("standalone", "true");
	} else {
		SetAttribute("standalone", "true");
	}
}

bool exml::Declaration::Generate(etk::UString& _data, int32_t _indent) const
{
	AddIndent(_data, _indent);
	_data += "<?";
	_data += m_value;
	exml::AttributeList::Generate(_data, _indent);
	_data += "?>\n";
	return true;
}

bool exml::Declaration::Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, exml::filePos& _filePos, exml::Document& _doc)
{
	EXML_VERBOSE("start parse : 'declaration' : '" << m_value << "'");
	m_pos = _filePos;
	// search end of the comment :
	for (int32_t iii=_pos; iii+1<_data.Size(); iii++) {
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
			DrawElementParsed(_data[iii], _filePos);
		#endif
		if (_filePos.Check(_data[iii])==true) {
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
		if (true == CheckAvaillable(_data[iii], true)) {
			// we find an attibute ==> create a new and parse it :
			exml::Attribute* attribute = new exml::Attribute();
			if (NULL==attribute) {
				CREATE_ERROR(_doc, _data, _pos, _filePos, " Allocation error ...");
				return false;
			}
			_pos = iii;
			if (false==attribute->Parse(_data, _pos, _caseSensitive, _filePos, _doc)) {
				delete(attribute);
				return false;
			}
			iii = _pos;
			m_listAttribute.PushBack(attribute);
			continue;
		}
	}
	CREATE_ERROR(_doc, _data, _pos, _filePos, "Text got end of file without finding end node");
	_pos = _data.Size();
	return false;
}


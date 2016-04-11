/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <exml/Comment.h>
#include <exml/debug.h>
#include <exml/Document.h>

static bool isWhiteChar(char32_t _val) {
	if(    _val == ' '
	    || _val == '\t'
	    || _val == '\n'
	    || _val == '\r') {
		return true;
	}
	return false;
}

ememory::SharedPtr<exml::Comment> exml::Comment::create() {
	return ememory::SharedPtr<exml::Comment>(new exml::Comment());
}

bool exml::Comment::iParse(const std::string& _data, int32_t& _pos, bool _caseSensitive, exml::FilePos& _filePos, exml::Document& _doc) {
	EXML_VERBOSE("start parse : 'comment'");
	m_pos = _filePos;
	exml::FilePos tmpPos;
	int32_t white = countWhiteChar(_data, _pos, tmpPos);
	_filePos += tmpPos;
	// search end of the comment :
	for (size_t iii=_pos+white; iii+2<_data.size(); iii++) {
		#ifdef ENABLE_DISPLAY_PARSED_ELEMENT
		 drawElementParsed(_data[iii], _filePos);
		#endif
		if (_filePos.check(_data[iii]) == true) {
			continue;
		}
		if(    _data[iii] == '-'
		    && _data[iii+1] == '-'
		    && _data[iii+2] == '>') {
			_filePos += 2;
			// search whitespace :
			int32_t newEnd=iii;
			for( int32_t jjj=iii-1; jjj>_pos; jjj--) {
				if(isWhiteChar(_data[jjj]) == true) {
					newEnd = jjj;
				} else {
					break;
				}
			}
			// find end of value:
			m_value = std::string(_data, _pos+white, newEnd-(_pos+white));
			EXML_VERBOSE(" find comment '" << m_value << "'");
			_pos = iii+2;
			return true;
		}
	}
	_pos = _data.size();
	CREATE_ERROR(_doc, _data, _pos, _filePos, "comment got end of file without finding end node");
	return false;
}

bool exml::Comment::iGenerate(std::string& _data, int32_t _indent) const {
	addIndent(_data, _indent);
	_data += "<!--";
	_data += m_value;
	_data += "-->\n";
	return true;
}
/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <exml/EXmlDocument.h>
#include <exml/debug.h>


exml::EXmlDocument::EXmlDocument(void) : 
	m_charset(unicode::EDN_CHARSET_UTF8),
	m_caseSensitive(false)
{
	
}


bool exml::EXmlDocument::Generate(etk::UString& _data, int32_t _indent)
{
	for (int32_t iii=0; iii<m_listSub.Size(); iii++) {
		if (NULL!=m_listSub[iii]) {
			m_listSub[iii]->Generate(_data, _indent);
		}
	}
	return true;
}


bool exml::EXmlDocument::Parse(const etk::UString& _data, int32_t& _pos, bool _caseSensitive, ivec2& _filePos)
{
	EXML_DEBUG("start parse : 'document'");
	// in this case : no main node ...
	SubParse(_data, _pos, _caseSensitive, _filePos, true);
	return true;
}


bool exml::EXmlDocument::Parse(const etk::UString& _data)
{
	EXML_DEBUG("Start parsing document (type: string) size=" << _data.Size());
	// came from char ==> force in utf8 ...
	m_charset = unicode::EDN_CHARSET_UTF8;
	ivec2 filePos(0,1);
	int32_t parsePos = 0;
	return Parse(_data, parsePos, m_caseSensitive, filePos);
}

bool exml::EXmlDocument::Generate(etk::UString& _data)
{
	return false;
}

bool exml::EXmlDocument::Load(const etk::UString& _file)
{
	return false;
}

bool exml::EXmlDocument::Store(const etk::UString& _file)
{
	return false;
}

void exml::EXmlDocument::Display(void)
{
	etk::UString tmpp;
	Generate(tmpp, 0);
	EXML_INFO("Generated XML : \n" << tmpp);
}


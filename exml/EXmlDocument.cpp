/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <exml/EXmlDocument.h>


exml::EXmlDocument::EXmlDocument(void) : 
	m_charset(unicode::EDN_CHARSET_UNKNOW),
	m_caseSensitive(false)
{
	
}

bool Parse(const etk::UString& _data)
{
	// came from char ==> force in utf8 ...
	m_charset = unicode::EDN_CHARSET_UTF8;
	ivec2 filePos(1,1);
	int32_t ret = Parse(_data, 0, m_caseSensitive, filePos);
	return false;
}

bool Generate(etk::UString& _data)
{
	return false;
}

bool Load(const etk::UString& _file)
{
	return false;
}

bool Store(const etk::UString& _file)
{
	return false;
}



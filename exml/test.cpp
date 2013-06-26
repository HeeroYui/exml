/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <exml/test.h>
#include <etk/Debug.h>
#include <exml/debug.h>

#undef __class__
#define __class__	"test"

int main(int argc, const char *argv[])
{
	GeneralDebugSetLevel(etk::LOG_LEVEL_VERBOSE);
	exml::Document doc;
	etk::UString testString = ""
		"<   	 		 exemple\n   	>\n"
		"	<ex2 ploppp-plpl:erer=\"dfsdfsdfsdf\" lkmjmlk=\"156235\" sdfsdf=456321     />\n"
		"	<exlkjl-_dsfg./>\n"
		"	<ex2>\n"
		"		Text example ...\n"
//		"		<!--a really simple comment -- !!! [[]	] <   	 		 exemple\n   	-->\n"
//		"		<![CDATA[CDATA_EXEMPLE slkdjf l ksjdflks fsd s,dn fsfn >   < < S!! ]]>\n"
		"	</ex2>\n"
		"</exemple>\n";
	EXML_DEBUG("start parsing : \n" << testString);
	doc.Parse(testString);
	doc.Display();
	return false;
}


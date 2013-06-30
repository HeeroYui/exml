/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <exml/test.h>
#include <etk/Debug.h>
#include <etk/Vector.h>
#include <exml/debug.h>

#undef __class__
#define __class__	"test"

class testCheck
{
	public:
		etk::UString m_ref;
		etk::UString m_input;
		int32_t m_errorPos; // -1 : no error , 1 : parsing error, 2 generation error, 3 comparaison error ????
		testCheck(void) {};
		void Set(const etk::UString& _ref, int32_t _pos, const etk::UString& _input)
		{
			m_ref = _ref;
			m_input = _input;
			m_errorPos = _pos;
		}
};

etk::Vector<testCheck> l_list;

void Init(void)
{
	etk::UString reference;
	etk::UString input;
	testCheck check;
	
	// ======================================================
	check.Set("test exml::Element", -2, "");
	l_list.PushBack(check);
	// ======================================================
	reference = "<exemple/>\n";
	check.Set(reference,
	          -1,
	          "<exemple/>\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	          "<    \t\r   exemple/>\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          -1,
	          "<    \t\r   exemple    \t\r\r\r\n   		 		 \t\t />\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          1,
	          "<       exemple   <  >\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          1,
	          "<       exemple   / />\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          1,
	          "<       exemple   ?  />\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          1,
	          "<       exemple   *  />\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          1,
	          "<  .     exemple   <  />\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          1,
	          "<!       exemple   < />\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          1,
	          "<!-       exemple   <  />\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set(reference,
	          1,
	          "<       exemple   < />\n");
	l_list.PushBack(check);
	check.Set("<exemple--/>\n",
	          1,
	          "<exemple-->\n");
	l_list.PushBack(check);
	check.Set("<exemple/>\n",
	          1,
	          "<exemple>\n</exemple sdfgsdfg>\n");
	l_list.PushBack(check);
	// ======================================================
	check.Set("test element exml::Attribute ", -2, "");
	l_list.PushBack(check);
	// ======================================================
	check.Set("<elementtt attr=\"plop\"/>\n",
	          -1,
	          "<elementtt attr=\"plop\"/>\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<elementtt attr=\"plop\"/>\n",
	          -1,
	          "<elementtt attr=plop/>\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<elementtt attr=\"234345@3452345_.'\"/>\n",
	          -1,
	          "<elementtt attr=234345@3452345_.'     />\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<elementtt attr=\"plop\"/>\n",
	          -1,
	          "<elementtt attr   =\"plop\"/>\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<elementtt attr=\"plop\"/>\n",
	          -1,
	          "<elementtt attr=    \"plop\"/>\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<elementtt attr=\"plop\"/>\n",
	          -1,
	          "<elementtt attr\n=\n\"plop\"/>\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<elementtt attr=\"plop\"/>\n",
	          -1,
	          "<elementtt attr=plop/>\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<elementtt attr=\"plop\"/>\n",
	          -1,
	          "<elementtt attr    \n  =   \n\t plop/>\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<elementtt attr=\"\"/>\n",
	          -1,
	          "<elementtt attr=\"\"/>\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<elementtt attr=\"\"/>\n",
	          -1,
	          "<elementtt attr=/>\n");
	l_list.PushBack(check);
	// ======================================================
	check.Set("test exml::Declaration", -2, "");
	l_list.PushBack(check);
	// ======================================================
	check.Set("<?testDeclaration?>\n",
	          -1,
	          "<?testDeclaration?>\n");
	l_list.PushBack(check);
	// ======================================================
	check.Set("test Declaration exml::Attribute", -2, "");
	l_list.PushBack(check);
	// ======================================================
	check.Set("<?xml attr=\"plop\"?>\n",
	          -1,
	          "<?xml attr=\"plop\"?>\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<?xml attr=\"plop\"?>\n",
	          -1,
	          "<?xml attr=plop?>\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<?xml attr=\"234345@3452345_.'\"?>\n",
	          -1,
	          "<?xml attr=234345@3452345_.'     ?>\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<?xml attr=\"plop\"?>\n",
	          -1,
	          "<?xml attr   =\"plop\"?>\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<?xml attr=\"plop\"?>\n",
	          -1,
	          "<?xml attr=    \"plop\"?>\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<?xml attr=\"plop\"?>\n",
	          -1,
	          "<?xml attr\n=\n\"plop\"?>\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<?xml attr=\"plop\"?>\n",
	          -1,
	          "<?xml attr=plop?>\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<?xml attr=\"plop\"?>\n",
	          -1,
	          "<?xml attr    \n  =   \n\t plop?>\n");
	l_list.PushBack(check);
	// ======================================================
	check.Set("test exml::Comment", -2, "");
	l_list.PushBack(check);
	// ======================================================
	check.Set("<!--exemple-->\n",
	          -1,
	          "<!--exemple-->\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<!--exemple-->\n",
	          -1,
	          "<!--   \t \t\t exemple          \n\n\n\t-->\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<!---- exemple-->\n",
	          -1,
	          "<!--   -- exemple -->\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<!--> exemple-->\n",
	          -1,
	          "<!--> exemple -->\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<!--exemple-->\n",
	          1,
	          "<!--   ---> exemple -->\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<!--exemple-->\n",
	          1,
	          "<!-- ssdfgdfg  >\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<!---->\n",
	          -1,
	          "<!---->\n");
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("<!--<.:!*%^$0945-	'(-	&<<< >>>	'&	(	'(	'-' <elementPouris>-->\n",
	          -1,
	          "<!-- <.:!*%^$0945-	'(-	&<<< >>>	'&	(	'(	'-' <elementPouris>	-->\n");
	l_list.PushBack(check);
	// ======================================================
	check.Set("test all", -2, "");
	l_list.PushBack(check);
	// ======================================================
	reference= "<exemple>\n"
	           "	<ex2 ploppp-plpl:erer=\"dfsdfsdfsdf\" lkmjmlk=\"156235\" sdfsdf=\"456321\"/>\n"
	           "	<exlkjl-_dsfg./>\n"
	           "	<ex2>Text example ...</ex2>\n"
	           "</exemple>\n";
	input ="<   	 		 exemple\n   	>\n"
	       "	<ex2 ploppp-plpl:erer=\"dfsdfsdfsdf\" lkmjmlk=\"156235\" sdfsdf=456321     />\n"
	       "	<exlkjl-_dsfg./>\n"
	       "	<ex2>\n"
	       "		Text example ...\n"
	       "	</ex2>\n"
	       "</exemple>\n";
	check.Set(reference, -1, input);
	l_list.PushBack(check);
	// ------------------------------------------------------
	check.Set("", 1,
	       "<   	 		 exemple\n   	>\n"
	       "	<ex2 ploppp-plpl:erer=\"dfsdfsdfsdf\" lkmjmlk=\"156235\" sdfsdf=456321     />\n"
	       "	<exlkjl-_dsfg./>    >\n"
	       "	<ex2>\n"
	       "		Text example ...\n"
	       "	</ex2>\n"
	       "</exemple>\n");
	l_list.PushBack(check);
}

int main(int argc, const char *argv[])
{
	GeneralDebugSetLevel(etk::LOG_LEVEL_VERBOSE);
	Init();
	int32_t countError = 0;
	int32_t countSeparator = 0;
	int32_t sectionID = 0;
	for (int32_t iii=0 ; iii<l_list.Size() ; iii++) {
		int32_t jjj= iii-countSeparator+1;
		if (l_list[iii].m_errorPos==-2) {
			countSeparator++;
			sectionID = 0;
			EXML_INFO("-------------------------------------------------------------");
			EXML_INFO("-- " << l_list[iii].m_ref);
			EXML_INFO("-------------------------------------------------------------");
			continue;
		}
		sectionID++;
		exml::Document doc;
		etk::UString out("");
		//EXML_DEBUG("parse : \n" << l_list[iii].m_input);
		if (false==doc.Parse(l_list[iii].m_input)) {
			if (l_list[iii].m_errorPos==1) {
				EXML_INFO("[TEST] " << sectionID << ":" << jjj << " {  OK  } Parsing in error (correct result)");
			} else {
				EXML_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } Parsing might be OK");
				EXML_ERROR("parse : \n" << l_list[iii].m_input);
				countError++;
			}
			continue;
		}
		if (l_list[iii].m_errorPos==1) {
			EXML_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } Parsing might be in error ...");
			EXML_ERROR("parse : \n" << l_list[iii].m_input);
			doc.Display();
			countError++;
			continue;
		}
		if (false == doc.Generate(out)) {
			if (l_list[iii].m_errorPos==2) {
				EXML_INFO("[TEST] " << sectionID << ":" << jjj << " {  OK  } generate in error (correct result)");
			} else {
				EXML_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } Generate output might be OK");
				EXML_ERROR("generate : \n" << out);
				countError++;
			}
			continue;
		}
		if (l_list[iii].m_errorPos==2) {
			EXML_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } Generating might be in error ...");
			countError++;
			continue;
		}
		if (l_list[iii].m_ref != out) {
			if (l_list[iii].m_errorPos==3) {
				EXML_INFO("[TEST] " << sectionID << ":" << jjj << " {  OK  } Result in error (normal case)");
			} else {
				EXML_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } different output");
				EXML_ERROR("generate : \n" << out);
				EXML_ERROR("reference : \n" << l_list[iii].m_ref);
				countError++;
			}
			continue;
		}
		if (l_list[iii].m_errorPos==3) {
			EXML_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR} checking result might be in error...");
			EXML_ERROR("generate : \n" << out);
			EXML_ERROR("reference : \n" << l_list[iii].m_ref);
			countError++;
			continue;
		}
		EXML_INFO("[TEST] " << sectionID << ":" << jjj << " {  OK  }");
	}
	if (countError>0) {
		EXML_ERROR("[TEST] produce " << countError << " error on " << l_list.Size()-countSeparator << " test");
	} else {
		EXML_INFO("[TEST] produce " << countError << " error on " << l_list.Size()-countSeparator << " test");
	}
	return 0;
}


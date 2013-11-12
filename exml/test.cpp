/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#include <exml/test.h>
#include <exml/debug.h>
#include <vector>
#include <exml/debug.h>

#undef __class__
#define __class__ "test"

class testCheck {
	public:
		std::string m_ref;
		std::string m_input;
		int32_t m_errorPos; // -1 : no error , 1 : parsing error, 2 generation error, 3 comparaison error ????
		testCheck(void) {};
		void set(const std::string& _ref, int32_t _pos, const std::string& _input) {
			m_ref = _ref;
			m_input = _input;
			m_errorPos = _pos;
		}
};

std::vector<testCheck> l_list;

void init(void) {
	std::string reference;
	std::string input;
	testCheck check;
	
	//  == ====================================================
	check.set("test exml::Element", -2, "");
	l_list.push_back(check);
	//  == ====================================================
	reference = "<exemple/>\n";
	check.set(reference,
	          -1,
	          "<exemple/>\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set(reference,
	          -1,
	          "<    \t\r   exemple/>\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set(reference,
	          -1,
	          "<    \t\r   exemple    \t\r\r\r\n   		 		 \t\t />\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set(reference,
	          1,
	          "<       exemple   <  >\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set(reference,
	          1,
	          "<       exemple   / />\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set(reference,
	          1,
	          "<       exemple   ?  />\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set(reference,
	          1,
	          "<       exemple   *  />\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set(reference,
	          1,
	          "<  .     exemple   <  />\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set(reference,
	          1,
	          "<!       exemple   < />\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set(reference,
	          1,
	          "<!-       exemple   <  />\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set(reference,
	          1,
	          "<       exemple   < />\n");
	l_list.push_back(check);
	check.set("<exemple--/>\n",
	          1,
	          "<exemple-->\n");
	l_list.push_back(check);
	check.set("<exemple/>\n",
	          1,
	          "<exemple>\n</exemple sdfgsdfg>\n");
	l_list.push_back(check);
	//  == ====================================================
	check.set("test element exml::Attribute ", -2, "");
	l_list.push_back(check);
	//  == ====================================================
	check.set("<elementtt attr=\"plop\"/>\n",
	          -1,
	          "<elementtt attr=\"plop\"/>\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<elementtt attr=\"plop\"/>\n",
	          -1,
	          "<elementtt attr=plop/>\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<elementtt attr=\"234345@3452345_.'\"/>\n",
	          -1,
	          "<elementtt attr=234345@3452345_.'     />\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<elementtt attr=\"plop\"/>\n",
	          -1,
	          "<elementtt attr   =\"plop\"/>\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<elementtt attr=\"plop\"/>\n",
	          -1,
	          "<elementtt attr=    \"plop\"/>\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<elementtt attr=\"plop\"/>\n",
	          -1,
	          "<elementtt attr\n=\n\"plop\"/>\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<elementtt attr=\"plop\"/>\n",
	          -1,
	          "<elementtt attr=plop/>\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<elementtt attr=\"plop\"/>\n",
	          -1,
	          "<elementtt attr    \n  =   \n\t plop/>\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<elementtt attr=\"\"/>\n",
	          -1,
	          "<elementtt attr=\"\"/>\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<elementtt attr=\"\"/>\n",
	          -1,
	          "<elementtt attr=/>\n");
	l_list.push_back(check);
	//  == ====================================================
	check.set("test exml::Declaration", -2, "");
	l_list.push_back(check);
	//  == ====================================================
	check.set("<?testDeclaration?>\n",
	          -1,
	          "<?testDeclaration?>\n");
	l_list.push_back(check);
	//  == ====================================================
	check.set("test Declaration exml::Attribute", -2, "");
	l_list.push_back(check);
	//  == ====================================================
	check.set("<?xml attr=\"plop\"?>\n",
	          -1,
	          "<?xml attr=\"plop\"?>\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<?xml attr=\"plop\"?>\n",
	          -1,
	          "<?xml attr=plop?>\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<?xml attr=\"234345@3452345_.'\"?>\n",
	          -1,
	          "<?xml attr=234345@3452345_.'     ?>\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<?xml attr=\"plop\"?>\n",
	          -1,
	          "<?xml attr   =\"plop\"?>\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<?xml attr=\"plop\"?>\n",
	          -1,
	          "<?xml attr=    \"plop\"?>\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<?xml attr=\"plop\"?>\n",
	          -1,
	          "<?xml attr\n=\n\"plop\"?>\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<?xml attr=\"plop\"?>\n",
	          -1,
	          "<?xml attr=plop?>\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<?xml attr=\"plop\"?>\n",
	          -1,
	          "<?xml attr    \n  =   \n\t plop?>\n");
	l_list.push_back(check);
	//  == ====================================================
	check.set("test exml::Comment", -2, "");
	l_list.push_back(check);
	//  == ====================================================
	check.set("<!--exemple-->\n",
	          -1,
	          "<!--exemple-->\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<!--exemple-->\n",
	          -1,
	          "<!--   \t \t\t exemple          \n\n\n\t-->\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<!---- exemple-->\n",
	          -1,
	          "<!--   -- exemple -->\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<!--> exemple-->\n",
	          -1,
	          "<!--> exemple -->\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<!--exemple-->\n",
	          1,
	          "<!--   ---> exemple -->\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<!--exemple-->\n",
	          1,
	          "<!-- ssdfgdfg  >\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<!---->\n",
	          -1,
	          "<!---->\n");
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("<!--<.:!*%^$0945-	'(-	&<<< >>>	'&	(	'(	'-' <elementPouris>-->\n",
	          -1,
	          "<!-- <.:!*%^$0945-	'(-	&<<< >>>	'&	(	'(	'-' <elementPouris>	-->\n");
	l_list.push_back(check);
	//  == ====================================================
	check.set("test all", -2, "");
	l_list.push_back(check);
	//  == ====================================================
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
	check.set(reference, -1, input);
	l_list.push_back(check);
	// ------------------------------------------------------
	check.set("", 1,
	       "<   	 		 exemple\n   	>\n"
	       "	<ex2 ploppp-plpl:erer=\"dfsdfsdfsdf\" lkmjmlk=\"156235\" sdfsdf=456321     />\n"
	       "	<exlkjl-_dsfg./>    >\n"
	       "	<ex2>\n"
	       "		Text example ...\n"
	       "	</ex2>\n"
	       "</exemple>\n");
	l_list.push_back(check);
}

int main(int argc, const char *argv[]) {
	debug::setGeneralLevel(etk::logLevelVerbose);
	init();
	int32_t countError = 0;
	int32_t countSeparator = 0;
	int32_t sectionID = 0;
	for (int32_t iii=0 ; iii<l_list.size() ; iii++) {
		int32_t jjj= iii-countSeparator+1;
		if (l_list[iii].m_errorPos == -2) {
			countSeparator++;
			sectionID = 0;
			EXML_INFO("-------------------------------------------------------------");
			EXML_INFO("-- " << l_list[iii].m_ref);
			EXML_INFO("-------------------------------------------------------------");
			continue;
		}
		sectionID++;
		exml::Document doc;
		std::string out("");
		//EXML_DEBUG("parse : \n" << l_list[iii].m_input);
		if (false == doc.parse(l_list[iii].m_input)) {
			if (l_list[iii].m_errorPos == 1) {
				EXML_INFO("[TEST] " << sectionID << ":" << jjj << " {  OK  } Parsing in error (correct result)");
			} else {
				EXML_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } Parsing might be OK");
				EXML_ERROR("parse : \n" << l_list[iii].m_input);
				countError++;
			}
			continue;
		}
		if (l_list[iii].m_errorPos == 1) {
			EXML_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } Parsing might be in error ...");
			EXML_ERROR("parse : \n" << l_list[iii].m_input);
			doc.display();
			countError++;
			continue;
		}
		if (false == doc.generate(out)) {
			if (l_list[iii].m_errorPos == 2) {
				EXML_INFO("[TEST] " << sectionID << ":" << jjj << " {  OK  } generate in error (correct result)");
			} else {
				EXML_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } generate output might be OK");
				EXML_ERROR("generate : \n" << out);
				countError++;
			}
			continue;
		}
		if (l_list[iii].m_errorPos == 2) {
			EXML_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } Generating might be in error ...");
			countError++;
			continue;
		}
		if (l_list[iii].m_ref != out) {
			if (l_list[iii].m_errorPos == 3) {
				EXML_INFO("[TEST] " << sectionID << ":" << jjj << " {  OK  } Result in error (normal case)");
			} else {
				EXML_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR } different output");
				EXML_ERROR("generate : \n" << out);
				EXML_ERROR("reference : \n" << l_list[iii].m_ref);
				countError++;
			}
			continue;
		}
		if (l_list[iii].m_errorPos == 3) {
			EXML_ERROR("[TEST] " << sectionID << ":" << jjj << " {ERROR} checking result might be in error...");
			EXML_ERROR("generate : \n" << out);
			EXML_ERROR("reference : \n" << l_list[iii].m_ref);
			countError++;
			continue;
		}
		EXML_INFO("[TEST] " << sectionID << ":" << jjj << " {  OK  }");
	}
	if (countError>0) {
		EXML_ERROR("[TEST] produce " << countError << " error on " << l_list.size()-countSeparator << " test");
	} else {
		EXML_INFO("[TEST] produce " << countError << " error on " << l_list.size()-countSeparator << " test");
	}
	return 0;
}


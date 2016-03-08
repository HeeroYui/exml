/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <test-debug/debug.h>
#include <vector>
#include <gtest/gtest.h>
#include <etk/os/FSNode.h>

//#include "exmlTestDocument.h"
#include "exmlTestElement.h"
#include "exmlTestAttribute.h"
#include "exmlTestDeclaration.h"
#include "exmlTestAll.h"

#undef __class__
#define __class__ "exml::test"

int main(int argc, const char *argv[]) {
	// init Google test :
	::testing::InitGoogleTest(&argc, const_cast<char **>(argv));
	// the only one init for etk:
	elog::setLevel(elog::logLevelNone);
	for (int32_t iii=0; iii<argc ; ++iii) {
		std::string data = argv[iii];
		if (data == "-l0") {
			elog::setLevel(elog::logLevelNone);
		} else if (data == "-l1") {
			elog::setLevel(elog::logLevelCritical);
		} else if (data == "-l2") {
			elog::setLevel(elog::logLevelError);
		} else if (data == "-l3") {
			elog::setLevel(elog::logLevelWarning);
		} else if (data == "-l4") {
			elog::setLevel(elog::logLevelInfo);
		} else if (data == "-l5") {
			elog::setLevel(elog::logLevelDebug);
		} else if (data == "-l6") {
			elog::setLevel(elog::logLevelVerbose);
		} else if (    data == "-h"
		            || data == "--help") {
			std::cout << "Help : " <<std::endl;
			std::cout << "    ./xxx [options]" <<std::endl;
			std::cout << "        -l0: debug None" <<std::endl;
			std::cout << "        -l1: debug Critical" <<std::endl;
			std::cout << "        -l2: debug Error" <<std::endl;
			std::cout << "        -l3: debug Warning" <<std::endl;
			std::cout << "        -l4: debug Info" <<std::endl;
			std::cout << "        -l5: debug Debug" <<std::endl;
			std::cout << "        -l6: debug Verbose" <<std::endl;
			std::cout << "        -h/--help: this help" <<std::endl;
			exit(0);
		}
	}
	etk::setArgZero(argv[0]);
	etk::initDefaultFolder("exml_test");
	return RUN_ALL_TESTS();
}

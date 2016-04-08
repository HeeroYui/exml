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
#include <etk/etk.h>

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
	etk::init(argc, argv);
	for (int32_t iii=0; iii<argc ; ++iii) {
		std::string data = argv[iii];
		if (    data == "-h"
		     || data == "--help") {
			TEST_PRINT("Help : ");
			TEST_PRINT("    ./xxx [options]");
			TEST_PRINT("        -h/--help: this help");
			exit(0);
		}
	}
	etk::initDefaultFolder("exml_test");
	return RUN_ALL_TESTS();
}

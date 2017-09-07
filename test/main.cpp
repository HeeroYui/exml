/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <test-debug/debug.hpp>
#include <etest/etest.hpp>
#include <etk/os/FSNode.hpp>
#include <etk/etk.hpp>

int main(int argc, const char *argv[]) {
	// init Google test :
	::testing::InitGoogleTest(&argc, const_cast<char **>(argv));
	// the only one init for etk:
	etk::init(argc, argv);
	for (int32_t iii=0; iii<argc ; ++iii) {
		etk::String data = argv[iii];
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

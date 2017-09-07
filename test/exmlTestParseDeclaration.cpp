/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include "exmlTestCommon.hpp"
#include <etest/etest.hpp>



TEST(TestParseDeclaration, testBase) {
	exmlLocalTest("<?testDeclaration?>\n", "<?testDeclaration?>\n", -1);
}
TEST(TestParseDeclaration, testAttribute) {
	exmlLocalTest("<?xml attr=\"plop\"?>\n", "<?xml attr=\"plop\"?>\n", -1);
}
TEST(TestParseDeclaration, testNoQuote) {
	exmlLocalTest("<?xml attr=\"plop\"?>\n", "<?xml attr=plop?>\n", -1);
}
TEST(TestParseDeclaration, testNumberNoQuote) {
	exmlLocalTest("<?xml attr=\"234345@3452345_.'\"?>\n", "<?xml attr=234345@3452345_.'     ?>\n", -1);
}
TEST(TestParseDeclaration, testSpace1) {
	exmlLocalTest("<?xml attr=\"plop\"?>\n", "<?xml attr   =\"plop\"?>\n", -1);
}
TEST(TestParseDeclaration, testSpace2) {
	exmlLocalTest("<?xml attr=\"plop\"?>\n", "<?xml attr=    \"plop\"?>\n", -1);
}
TEST(TestParseDeclaration, testMultiline) {
	exmlLocalTest("<?xml attr=\"plop\"?>\n", "<?xml attr\n=\n\"plop\"?>\n", -1);
}
TEST(TestParseDeclaration, testAll) {
	exmlLocalTest("<?xml attr=\"p65421lop\"?>\n", "<?xml attr    \n  =   \n\t p65421lop?>\n", -1);
}


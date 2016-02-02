/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include "exmlTestCommon.h"
#include <gtest/gtest.h>


TEST(TestDeclaration, testBase) {
	exmlLocalTest("<?testDeclaration?>\n", "<?testDeclaration?>\n", -1);
}
TEST(TestDeclaration, testAttribute) {
	exmlLocalTest("<?xml attr=\"plop\"?>\n", "<?xml attr=\"plop\"?>\n", -1);
}
TEST(TestDeclaration, testNoQuote) {
	exmlLocalTest("<?xml attr=\"plop\"?>\n", "<?xml attr=plop?>\n", -1);
}
TEST(TestDeclaration, testNumberNoQuote) {
	exmlLocalTest("<?xml attr=\"234345@3452345_.'\"?>\n", "<?xml attr=234345@3452345_.'     ?>\n", -1);
}
TEST(TestDeclaration, testSpace1) {
	exmlLocalTest("<?xml attr=\"plop\"?>\n", "<?xml attr   =\"plop\"?>\n", -1);
}
TEST(TestDeclaration, testSpace2) {
	exmlLocalTest("<?xml attr=\"plop\"?>\n", "<?xml attr=    \"plop\"?>\n", -1);
}
TEST(TestDeclaration, testMultiline) {
	exmlLocalTest("<?xml attr=\"plop\"?>\n", "<?xml attr\n=\n\"plop\"?>\n", -1);
}
TEST(TestDeclaration, testAll) {
	exmlLocalTest("<?xml attr=\"p65421lop\"?>\n", "<?xml attr    \n  =   \n\t p65421lop?>\n", -1);
}


/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include "exmlTestCommon.hpp"
#include <gtest/gtest.h>


static std::string refOutputElement("<exemple/>\n");

TEST(TestParseElement, testBase) {
	exmlLocalTest(refOutputElement, "<exemple/>\n", -1);
}
TEST(TestParseElement, testMultiline) {
	exmlLocalTest(refOutputElement, "<    \t\r   exemple/>\n", -1);
}
TEST(TestParseElement, testMultilineMultiTabbed) {
	exmlLocalTest(refOutputElement, "<    \t\r   exemple    \t\r\r\r\n   		 		 \t\t />\n", -1);
}
TEST(TestParseElement, testWrongStart) {
	exmlLocalTest(refOutputElement, "<       exemple   <  >\n", 1);
}
TEST(TestParseElement, testMultipleSlash) {
	exmlLocalTest(refOutputElement, "<       exemple   / />\n", 1);
}
TEST(TestParseElement, testExclamationPresence) {
	exmlLocalTest(refOutputElement, "<       exemple   ?  />\n", 1);
}
TEST(TestParseElement, testStarPresence) {
	exmlLocalTest(refOutputElement, "<       exemple   *  />\n", 1);
}
TEST(TestParseElement, testDotPresent) {
	exmlLocalTest(refOutputElement, "<  .     exemple   <  />\n", 1);
}
TEST(TestParseElement, testWrong1) {
	exmlLocalTest(refOutputElement, "<!       exemple   < />\n", 1);
}
TEST(TestParseElement, testWrong2) {
	exmlLocalTest(refOutputElement, "<!-       exemple   <  />\n", 1);
}
TEST(TestParseElement, testWrong3) {
	exmlLocalTest(refOutputElement, "<       exemple   < />\n", 1);
}

TEST(TestParseElement, testBase2) {
	exmlLocalTest("<exemple--/>\n", "<exemple-->\n", 1);
}
TEST(TestParseElement, testBase3) {
	exmlLocalTest("<exemple/>\n", "<exemple>\n</exemple sdfgsdfg>\n", 1);
}


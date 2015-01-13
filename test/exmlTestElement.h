/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */


#ifndef __EXML_TEST_ELEMENT_H__
#define __EXML_TEST_ELEMENT_H__

#include "exmlTestCommon.h"
#include <gtest/gtest.h>


static std::string refOutputElement("<exemple/>\n");

TEST(TestElement, testBase) {
	exmlLocalTest(refOutputElement, "<exemple/>\n", -1);
}
TEST(TestElement, testMultiline) {
	exmlLocalTest(refOutputElement, "<    \t\r   exemple/>\n", -1);
}
TEST(TestElement, testMultilineMultiTabbed) {
	exmlLocalTest(refOutputElement, "<    \t\r   exemple    \t\r\r\r\n   		 		 \t\t />\n", -1);
}
TEST(TestElement, testWrongStart) {
	exmlLocalTest(refOutputElement, "<       exemple   <  >\n", 1);
}
TEST(TestElement, testMultipleSlash) {
	exmlLocalTest(refOutputElement, "<       exemple   / />\n", 1);
}
TEST(TestElement, testExclamationPresence) {
	exmlLocalTest(refOutputElement, "<       exemple   ?  />\n", 1);
}
TEST(TestElement, testStarPresence) {
	exmlLocalTest(refOutputElement, "<       exemple   *  />\n", 1);
}
TEST(TestElement, testDotPresent) {
	exmlLocalTest(refOutputElement, "<  .     exemple   <  />\n", 1);
}
TEST(TestElement, testWrong1) {
	exmlLocalTest(refOutputElement, "<!       exemple   < />\n", 1);
}
TEST(TestElement, testWrong2) {
	exmlLocalTest(refOutputElement, "<!-       exemple   <  />\n", 1);
}
TEST(TestElement, testWrong3) {
	exmlLocalTest(refOutputElement, "<       exemple   < />\n", 1);
}

TEST(TestElement, testBase2) {
	exmlLocalTest("<exemple--/>\n", "<exemple-->\n", 1);
}
TEST(TestElement, testBase3) {
	exmlLocalTest("<exemple/>\n", "<exemple>\n</exemple sdfgsdfg>\n", 1);
}

#endif

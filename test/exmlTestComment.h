/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */


#ifndef __EXML_TEST_COMMENT_H__
#define __EXML_TEST_COMMENT_H__

#include "exmlTestCommon.h"
#include <gtest/gtest.h>


TEST(TestComment, testBase) {
	exmlLocalTest("<!--exemple-->\n", "<!--exemple-->\n", -1);
}
TEST(TestComment, testMultiline) {
	exmlLocalTest("<!--exemple-->\n", "<!--   \t \t\t exemple          \n\n\n\t-->\n", -1);
}
TEST(TestComment, testTiretInComment) {
	exmlLocalTest("<!---- exemple-->\n", "<!--   -- exemple -->\n", -1);
}
TEST(TestComment, testWrongEndParsing) {
	exmlLocalTest("<!--> exemple-->\n", "<!--> exemple -->\n", -1);
}
TEST(TestComment, testMultipleEnd) {
	exmlLocalTest("<!--exemple-->\n", "<!--   ---> exemple -->\n", 1);
}
TEST(TestComment, testEndError) {
	exmlLocalTest("<!--exemple-->\n", "<!-- ssdfgdfg  >\n", 1);
}
TEST(TestComment, testNoCharInComment) {
	exmlLocalTest("<!---->\n", "<!---->\n", -1);
}
TEST(TestComment, testAll) {
	exmlLocalTest("<!--<.:!*%^$0945-	'(-	&<<< >>>	'&	(	'(	'-' <elementPouris>-->\n",
	              "<!-- <.:!*%^$0945-	'(-	&<<< >>>	'&	(	'(	'-' <elementPouris>	-->\n",
	              -1);
}

#endif

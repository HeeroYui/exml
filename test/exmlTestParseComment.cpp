/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include "exmlTestCommon.h"
#include <gtest/gtest.h>



TEST(TestParseComment, testBase) {
	exmlLocalTest("<!--exemple-->\n", "<!--exemple-->\n", -1);
}
TEST(TestParseComment, testMultiline) {
	exmlLocalTest("<!--exemple-->\n", "<!--   \t \t\t exemple          \n\n\n\t-->\n", -1);
}
TEST(TestParseComment, testTiretInComment) {
	exmlLocalTest("<!---- exemple-->\n", "<!--   -- exemple -->\n", -1);
}
TEST(TestParseComment, testWrongEndParsing) {
	exmlLocalTest("<!--> exemple-->\n", "<!--> exemple -->\n", -1);
}
TEST(TestParseComment, testMultipleEnd) {
	exmlLocalTest("<!--exemple-->\n", "<!--   ---> exemple -->\n", 1);
}
TEST(TestParseComment, testEndError) {
	exmlLocalTest("<!--exemple-->\n", "<!-- ssdfgdfg  >\n", 1);
}
TEST(TestParseComment, testNoCharInComment) {
	exmlLocalTest("<!---->\n", "<!---->\n", -1);
}
TEST(TestParseComment, testAll) {
	exmlLocalTest("<!--<.:!*%^$0945-	'(-	&<<< >>>	'&	(	'(	'-' <elementPouris>-->\n",
	              "<!-- <.:!*%^$0945-	'(-	&<<< >>>	'&	(	'(	'-' <elementPouris>	-->\n",
	              -1);
}

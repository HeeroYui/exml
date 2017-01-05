/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include "exmlTestCommon.hpp"
#include <gtest/gtest.h>



TEST(TestParseAttribute, testBase) {
	exmlLocalTest("<elementtt attr=\"plop\"/>\n",
	              "<elementtt attr=\"plop\"/>\n",
	              -1);
}
TEST(TestParseAttribute, testNoQuote) {
	exmlLocalTest("<elementtt attr=\"plop\"/>\n",
	              "<elementtt attr=plop/>\n",
	              -1);
}
TEST(TestParseAttribute, testNoQuoteNumber) {
	exmlLocalTest("<elementtt attr=\"234345@3452345_.'\"/>\n",
	              "<elementtt attr=234345@3452345_.'     />\n",
	              -1);
}
TEST(TestParseAttribute, testSpace1) {
	exmlLocalTest("<elementtt attr=\"plop\"/>\n",
	              "<elementtt attr   =\"plop\"/>\n",
	              -1);
}
TEST(TestParseAttribute, testSpace2) {
	exmlLocalTest("<elementtt attr=\"plop\"/>\n",
	              "<elementtt attr=    \"plop\"/>\n",
	              -1);
}
TEST(TestParseAttribute, testMultiline) {
	exmlLocalTest("<elementtt attr=\"plop\"/>\n",
	              "<elementtt attr\n=\n\"plop\"/>\n",
	              -1);
}
TEST(TestParseAttribute, testMultilineNoQuote) {
	exmlLocalTest("<elementtt attr=\"plop\"/>\n",
	              "<elementtt attr    \n  =   \n\t plop/>\n",
	              -1);
}
TEST(TestParseAttribute, testEmptyAttribute) {
	exmlLocalTest("<elementtt attr=\"\"/>\n",
	              "<elementtt attr=\"\"/>\n",
	              -1);
}
TEST(TestParseAttribute, testEmptyAttributeNoQuote) {
	exmlLocalTest("<elementtt attr=\"\"/>\n",
	              "<elementtt attr=/>\n",
	              -1);
}

TEST(TestParseAttribute, testEndAttributeError) {
	exmlLocalTest("",
	              "<elementtt attr",
	              1);
}


TEST(TestParseAttribute, testEndAttributeErrorMissingEqual) {
	exmlLocalTest("",
	              "<elementtt attr \"kjlkj\"/>\n",
	              1);
}

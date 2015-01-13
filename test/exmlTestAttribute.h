/**
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */


#ifndef __EXML_TEST_ATTRIBUTE_H__
#define __EXML_TEST_ATTRIBUTE_H__

#include "exmlTestCommon.h"
#include <gtest/gtest.h>


TEST(TestAttribute, testBase) {
	exmlLocalTest("<elementtt attr=\"plop\"/>\n",
	              "<elementtt attr=\"plop\"/>\n",
	              -1);
}
TEST(TestAttribute, testNoQuote) {
	exmlLocalTest("<elementtt attr=\"plop\"/>\n",
	              "<elementtt attr=plop/>\n",
	              -1);
}
TEST(TestAttribute, testNoQuoteNumber) {
	exmlLocalTest("<elementtt attr=\"234345@3452345_.'\"/>\n",
	              "<elementtt attr=234345@3452345_.'     />\n",
	              -1);
}
TEST(TestAttribute, testSpace1) {
	exmlLocalTest("<elementtt attr=\"plop\"/>\n",
	              "<elementtt attr   =\"plop\"/>\n",
	              -1);
}
TEST(TestAttribute, testSpace2) {
	exmlLocalTest("<elementtt attr=\"plop\"/>\n",
	              "<elementtt attr=    \"plop\"/>\n",
	              -1);
}
TEST(TestAttribute, testMultiline) {
	exmlLocalTest("<elementtt attr=\"plop\"/>\n",
	              "<elementtt attr\n=\n\"plop\"/>\n",
	              -1);
}
TEST(TestAttribute, testMultilineNoQuote) {
	exmlLocalTest("<elementtt attr=\"plop\"/>\n",
	              "<elementtt attr    \n  =   \n\t plop/>\n",
	              -1);
}
TEST(TestAttribute, testEmptyAttribute) {
	exmlLocalTest("<elementtt attr=\"\"/>\n",
	              "<elementtt attr=\"\"/>\n",
	              -1);
}
TEST(TestAttribute, testEmptyAttributeNoQuote) {
	exmlLocalTest("<elementtt attr=\"\"/>\n",
	              "<elementtt attr=/>\n",
	              -1);
}

#endif

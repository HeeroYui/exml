/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2016, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <test-debug/debug.h>
#include <exml/exml.h>
#include "read.h"

void appl::read() {
	exml::Document doc;
	TEST_INFO("parse");
	bool retParse = doc.parse("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"true\"?>"
	                          "<!-- my comment -->"
	                          "<exml attributeExample=\"my data attribute\">coucou</exml>");
	TEST_INFO("parse ret = " << retParse);
	TEST_INFO("Debug display of the tree:");
	doc.display();
	TEST_INFO("list of attribute:");
	for (auto it: doc.attributes) {
		TEST_INFO("	" << it);
	}
	TEST_INFO("list of sub-node:");
	for (const auto it: doc) {
		TEST_INFO("	" << it);
		if (it.isElement() == false) {
			continue;
		}
		exml::Element elem = it.toElement();
		if (elem.exist() == false) {
			continue;
		}
		TEST_INFO("		list of attribute:");
		for (auto itElem: elem.attributes) {
			TEST_INFO("			" << itElem);
		}
		TEST_INFO("		list of sub-node:");
		for (const auto itElem: elem) {
			TEST_INFO("			" << itElem);
		}
	}
}

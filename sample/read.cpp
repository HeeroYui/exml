/** @file
 * @author Edouard DUPIN
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

//! [exml_sample_read_all]
#include <test-debug/debug.h>
//! [exml_sample_include]
#include <exml/exml.h>
//! [exml_sample_include]
#include "read.h"


static void readFromFile() {
	//! [exml_sample_declare_doc]
	exml::Document doc;
	//! [exml_sample_declare_doc]
	//! [exml_sample_read_file]
	bool retParse = doc.load("DATA:read.xml");
	//! [exml_sample_read_file]
	TEST_INFO("parse ret = " << retParse);
	TEST_INFO("Debug display of the tree:");
	doc.display();
}

static void readFromString1() {
	exml::Document doc;
	TEST_INFO("parse");
	//! [exml_sample_read_stream1]
	std::string stream = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"true\"?>"
	                     "<!-- my comment -->"
	                     "<exml attributeExample=\"my data attribute\">coucou</exml>";
	bool retParse = doc.parse(stream);
	//! [exml_sample_read_stream1]
	TEST_INFO("parse ret = " << retParse);
	TEST_INFO("Debug display of the tree:");
	doc.display();
}

static void readFromString2() {
	exml::Document doc;
	TEST_INFO("parse");
	//! [exml_sample_read_stream2]
	std::string stream = "<?xml version='1.0' encoding='UTF-8' standalone='true'?>"
	                     "<!-- my comment -->"
	                     "<exml attributeExample='my data attribute'>coucou</exml>";
	bool retParse = doc.parse(stream);
	//! [exml_sample_read_stream2]
	TEST_INFO("parse ret = " << retParse);
	TEST_INFO("Debug display of the tree:");
	doc.display();
}


static void readFull() {
	exml::Document doc;
	TEST_INFO("parse");
	bool retParse = doc.load("DATA:read.xml");
	TEST_INFO("parse ret = " << retParse);
	TEST_INFO("Debug display of the tree:");
	doc.display();
	TEST_INFO("list of attribute:");
	for (auto it: doc.attributes) {
		TEST_INFO("	" << it);
	}
	TEST_INFO("list of sub-node:");
	for (const auto it: doc.nodes) {
		TEST_INFO("	" << it);
		if (it.isElement() == false) {
			continue;
		}
		exml::Element elem = it.toElement();
		if (elem.exist() == false) {
			continue;
		}
		TEST_INFO("		list of attribute:");
		for (const auto itElem: elem.attributes) {
			TEST_INFO("			" << itElem);
		}
		TEST_INFO("		list of sub-node:");
		for (const auto itElem: elem.nodes) {
			TEST_INFO("			" << itElem);
		}
	}
	TEST_INFO("	Direct get node exml:");
	//! [exml_sample_read_get_node]
	exml::Element element = doc.nodes["exml"];
	//! [exml_sample_read_get_node]
	TEST_INFO("		list of attribute:");
	//! [exml_sample_read_folow_attributes]
	for (const auto itElem: element.attributes) {
		std::string value = itElem.getValue();
		TEST_INFO("			'" << value << "'");
	}
	TEST_INFO("		list of attribute in C:");
	//! [exml_sample_read_folow_attributes]
	//! [exml_sample_read_folow_attributes_c]
	for (size_t iii=0; iii<element.attributes.size(); ++iii) {
		const exml::Attribute attr = element.attributes[iii];
		std::string value = attr.getValue();
		TEST_INFO("			'" << value << "'");
	}
	//! [exml_sample_read_folow_attributes_c]
	//! [exml_sample_read_get_direct_attribute]
	std::string attributeValue = element.attributes["attributeExample"];
	TEST_INFO("		direct get: '" << attributeValue << "'");
	//! [exml_sample_read_get_direct_attribute]
	TEST_INFO("		list of sub-node:");
	//! [exml_sample_read_folow_nodes]
	for (const auto itElem: element.nodes) {
		if (itElem.isElement() == true) {
			// get the <XXXX ... name
			std::string value = itElem.toElement().getValue();
			TEST_INFO("			'" << value << "'");
		} else {
			// simple debug for other type:
			TEST_INFO("			** " << itElem);
		}
	}
	//! [exml_sample_read_folow_nodes]
	TEST_INFO("		list of sub-node in C:");
	//! [exml_sample_read_folow_nodes_c]
	for (size_t iii=0; iii<element.nodes.size(); ++iii) {
		const exml::Node node = element.nodes[iii];
		if (node.isElement() == true) {
			// get the <XXXX ... name
			std::string value = node.toElement().getValue();
			TEST_INFO("			'" << value << "'");
		} else {
			// simple debug for other type:
			TEST_INFO("			** " << node);
		}
	}
	//! [exml_sample_read_folow_nodes_c]
	//! [exml_sample_read_get_all_under_string]
	std::string internalData = element.getText();
	//! [exml_sample_read_get_all_under_string]
	
}

void appl::read() {
	readFromFile();
	readFromString1();
	readFromString1();
	readFull();
}
//! [exml_sample_read_all]
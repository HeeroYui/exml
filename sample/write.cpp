/** @file
 * @author Edouard DUPIN
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <test-debug/debug.h>
#include <exml/exml.h>
#include "write.h"


static void writeToFile() {
	exml::Document doc;
	doc.nodes.add(exml::Declaration("2.5"));
	doc.nodes.add(exml::Element("node1"));
	doc.nodes.add(exml::Element("node2"));
	doc.nodes.add(exml::Comment("basic comment"));
	TEST_INFO("store");
	//! [exml_sample_write_file]
	bool retGenerate = doc.store("generate.xml");
	//! [exml_sample_write_file]
	TEST_INFO("parse ret = " << retGenerate);
	TEST_INFO("Debug display of the tree:");
	doc.display();
}

static void writeToString() {
	exml::Document doc;
	doc.nodes.add(exml::Declaration("2.5"));
	doc.nodes.add(exml::Element("node1"));
	doc.nodes.add(exml::Element("node2"));
	doc.nodes.add(exml::Comment("basic comment"));
	TEST_INFO("generate");
	//! [exml_sample_write_stream]
	std::string streamOut;
	bool retGenerate = doc.generate(streamOut);
	//! [exml_sample_write_stream]
	TEST_INFO("parse ret = " << retGenerate);
	TEST_INFO("Debug display of the tree:");
	doc.display();
}

static void writeAll() {
	exml::Document doc;
	//! [exml_sample_write_add_declaration]
	doc.nodes.add(exml::Declaration("2.5"));
	//! [exml_sample_write_add_declaration]
	//! [exml_sample_write_add_element]
	exml::Element elem = exml::Element("exml");
	doc.nodes.add(elem);
	//! [exml_sample_write_add_element]
	
	//! [exml_sample_write_add_attribute_simple]
	elem.attributes.set("attr1", "value attr 1");
	//! [exml_sample_write_add_attribute_simple]
	//! [exml_sample_write_add_attribute_complex]
	elem.attributes.add(exml::Attribute("attr2", "value attr 2"));
	//! [exml_sample_write_add_attribute_complex]
	doc.display();
	
	//! [exml_sample_write_rm_attribute]
	elem.attributes.remove("attr1");
	//! [exml_sample_write_rm_attribute]
	
	elem.nodes.add(exml::Element("node1"));
	elem.nodes.add(exml::Element("node2"));
	elem.nodes.add(exml::Element("node1"));
	
	//! [exml_sample_write_rm_node]
	// remove all node with this name
	elem.nodes.remove("attr1");
	//! [exml_sample_write_rm_node]
}


void appl::write() {
	writeToFile();
	writeToString();
	writeAll();
}


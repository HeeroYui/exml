/** @file
 * @author Edouard DUPIN
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

//! [exml_sample_write_all]
#include <test-debug/debug.hpp>
#include <exml/exml.hpp>
#include "write.hpp"


static void writeToFile() {
	exml::Document doc;
	doc.nodes.add(exml::Declaration("2.5"));
	doc.nodes.add(exml::Element("node1"));
	doc.nodes.add(exml::Element("node2"));
	doc.nodes.add(exml::Comment("basic comment"));
	TEST_INFO("store");
	//! [exml_sample_write_file]
	bool retGenerate = doc.store(etk::Path("generate.xml"));
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
	etk::String streamOut;
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


/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <etest/etest.hpp>
#include <test-debug/debug.hpp>
#include <exml/exml.hpp>
#include <exml/Element.hpp>
#include <exml/Comment.hpp>


TEST(TestElement, create) {
	exml::Element myElement("NodeName");
	EXPECT_EQ(myElement.getType(), exml::nodeType::element);
}

TEST(TestElement, createCopy) {
	exml::Element myElement("NodeName");
	exml::Element myOtherElement(myElement);
	//EXPECT_EQ(myElement, myOtherElement);
}

TEST(TestElement, createAssignement) {
	exml::Element myElement("NodeName");
	exml::Element myOtherElement;
	myOtherElement = myElement;
	//EXPECT_EQ(myElement, myOtherElement);
}

TEST(TestElement, moveInAllElement ) {
	exml::Document doc;
	doc.parse("<elem><elem1/><elem2/></elem>");
	for (auto it: doc.nodes) {
		EXPECT_EQ(it.getValue(), "elem");
	}
	for (const auto it: doc.nodes) {
		EXPECT_EQ(it.getValue(), "elem");
	}
}

TEST(TestElement, getText1 ) {
	exml::Element myElement("NodeName");
	EXPECT_EQ(myElement.getText(), "");
}

TEST(TestElement, getText2 ) {
	exml::Element myElement("NodeName");
	myElement.nodes.add(exml::Element("jkjhkjhkh"));
	EXPECT_EQ(myElement.getText(), "<jkjhkjhkh/>\n");
}


TEST(TestElement, getTypeId ) {
	exml::Element myElement("NodeName");
	EXPECT_EQ(myElement.nodes.getType(1), exml::nodeType::unknow);
}

TEST(TestElement, getNamed ) {
	exml::Element myElement("NodeName");
	EXPECT_EQ(myElement.nodes["jkjhkjhkh"].exist(), false);
}

TEST(TestElement, getNamedConst ) {
	const exml::Element myElement("NodeName");
	EXPECT_EQ(myElement.nodes["jkjhkjhkh"].exist(), false);
}

TEST(TestElement, operatorCrochetConst ) {
	const exml::Element myElement("NodeName");
	EXPECT_EQ(myElement.nodes[465].exist(), false);
}

TEST(TestElement, append ) {
	exml::Element myElement("NodeName");
	EXPECT_EQ(myElement.nodes.size(), 0);
	myElement.nodes.add(exml::Element("jkjhkjhkh"));
	EXPECT_EQ(myElement.nodes.size(), 1);
	EXPECT_EQ(myElement.nodes["jkjhkjhkh"].exist(), true);
	EXPECT_EQ(myElement.nodes.size(), 1);
}

TEST(TestElement, clear ) {
	exml::Element myElement("NodeName");
	EXPECT_EQ(myElement.nodes.size(), 0);
	myElement.nodes.add(exml::Element("jkjhkjhkh"));
	EXPECT_EQ(myElement.nodes.size(), 1);
	EXPECT_EQ(myElement.nodes["jkjhkjhkh"].exist(), true);
	EXPECT_EQ(myElement.nodes.size(), 1);
	myElement.clear();
	EXPECT_EQ(myElement.nodes.size(), 0);
}



TEST(TestElement, emptyElement ) {
	exml::Comment myComment("NodeName");
	exml::Element myElement = myComment.toElement();
	EXPECT_EQ(myElement.exist(), false);
	myElement.nodes.size();
	myElement.nodes[55];
	myElement.nodes.add(exml::Comment("kjhlkj"));
	myElement.getValue();
	myElement.setValue("lkjhlk");
	myElement.getText();
	myElement.nodes.getType(1);
	myElement.nodes["jkjhkjhkh"];
	myElement.clear();
}


TEST(TestElement, emptyElementConst ) {
	exml::Comment myComment("NodeName");
	const exml::Element myElement = myComment.toElement();
	EXPECT_EQ(myElement.exist(), false);
	myElement.nodes.size();
	myElement.nodes[55];
	myElement.getType();
	myElement.getValue();
	myElement.getText();
	myElement.nodes.getType(1);
	myElement.nodes["jkjhkjhkh"];
}


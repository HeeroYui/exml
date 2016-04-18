/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <gtest/gtest.h>
#include <exml/exml.h>
#include <exml/Attribute.h>


TEST(TestAttribute, create) {
	exml::Attribute myAttribute("nameAttribute", "valueAttribute");
	EXPECT_EQ(myAttribute.getType(), exml::nodeType::attribute);
}

TEST(TestAttribute, createCopy) {
	exml::Attribute myAttribute("nameAttribute", "valueAttribute");
	exml::Attribute myOtherAttribute(myAttribute);
	//EXPECT_EQ(myAttribute, myOtherAttribute);
}

TEST(TestAttribute, createAssignement) {
	exml::Attribute myAttribute("nameAttribute", "valueAttribute");
	exml::Attribute myOtherAttribute;
	myOtherAttribute = myAttribute;
	//EXPECT_EQ(myAttribute, myOtherAttribute);
}

TEST(TestAttribute, setGetValue) {
	exml::Attribute myAttribute("nameAttribute", "valueAttribute");
	EXPECT_EQ(myAttribute.getValue(), "valueAttribute");
	myAttribute.setValue("new value");
	EXPECT_EQ(myAttribute.getValue(), "new value");
}


TEST(TestAttribute, setGetName) {
	exml::Attribute myAttribute("nameAttribute", "valueAttribute");
	EXPECT_EQ(myAttribute.getName(), "nameAttribute");
	myAttribute.setName("newName");
	EXPECT_EQ(myAttribute.getName(), "newName");
}

TEST(TestAttribute, clear) {
	exml::Attribute myAttribute("nameAttribute", "valueAttribute");
	myAttribute.clear();
}


TEST(TestAttribute, nullElement) {
	exml::Element myElement("NodeName");
	
	exml::Attribute myAttribute = myElement.attributes[65465465];
	EXPECT_EQ(myAttribute.exist(), false);
	myAttribute.setName("lkjlkj");
	myAttribute.getName();
	myAttribute.setValue("kljhkljhkjh");
	myAttribute.getValue();
	myAttribute.clear();
}

TEST(TestAttribute, moveInAllElement ) {
	exml::Document doc;
	doc.parse("<elem valA=\"plop\"/>");
	exml::Element elem = doc.nodes["elem"];
	for (auto it: elem.attributes) {
		EXPECT_EQ(it.getName(), "valA");
		EXPECT_EQ(it.getValue(), "plop");
	}
}

TEST(TestAttribute, setterNew ) {
	exml::Element elem("elem");
	elem.attributes.set("valA", "coucou");
	EXPECT_EQ(elem.attributes["valA"], "coucou");
}
TEST(TestAttribute, setterRewrite ) {
	exml::Element elem("elem");
	elem.attributes.set("valA", "coucou");
	EXPECT_EQ(elem.attributes["valA"], "coucou");
	elem.attributes.set("valA", "coucou2");
	EXPECT_EQ(elem.attributes["valA"], "coucou2");
}
TEST(TestAttribute, getpair ) {
	exml::Element elem("elem");
	elem.attributes.set("valA", "coucou");
	EXPECT_EQ(elem.attributes.getPair(0).first, "valA");
	EXPECT_EQ(elem.attributes.getPair(0).second, "coucou");
	EXPECT_EQ(elem.attributes.getPair(1).first, "");
	EXPECT_EQ(elem.attributes.getPair(1).second, "");
}

TEST(TestAttribute, get ) {
	exml::Element elem("elem");
	elem.attributes.set("valA", "plop");
	EXPECT_EQ(elem.attributes["valA"], "plop");
	EXPECT_EQ(elem.attributes["qsdfsdf"], "");
}

TEST(TestAttribute, exist ) {
	exml::Element elem("elem");
	elem.attributes.set("valA", "plop");
	EXPECT_EQ(elem.attributes.exist("valA"), true);
	EXPECT_EQ(elem.attributes.exist("qsdfsdf"), false);
}

TEST(TestAttribute, remove ) {
	exml::Element elem("elem");
	elem.attributes.set("valA", "plop");
	EXPECT_EQ(elem.attributes.exist("valA"), true);
	elem.attributes.remove("valA");
	EXPECT_EQ(elem.attributes.exist("valA"), false);
}



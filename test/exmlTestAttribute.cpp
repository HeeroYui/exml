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
	EXPECT_EQ(myAttribute.getType(), exml::nodeType_attribute);
}

TEST(TestAttribute, createCopy) {
	exml::Attribute myAttribute("nameAttribute", "valueAttribute");
	exml::Attribute myOtherAttribute(myAttribute);
	//EXPECT_EQ(myAttribute, myOtherAttribute);
}

TEST(TestAttribute, createAssignement) {
	exml::Attribute myAttribute("nameAttribute", "valueAttribute");
	exml::Attribute myOtherAttribute = myAttribute;
	//EXPECT_EQ(myAttribute, myOtherAttribute);
}



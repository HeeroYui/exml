/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#include <gtest/gtest.h>
#include <exml/exml.h>
#include <exml/Element.h>


TEST(TestElement, create) {
	exml::Element myElement("NodeName");
	//EXPECT_EQ(myElement.getType(), exml::nodeType_element);
}

TEST(TestElement, createCopy) {
	exml::Element myElement("NodeName");
	exml::Element myOtherElement(myElement);
	//EXPECT_EQ(myElement, myOtherElement);
}

TEST(TestElement, createAssignement) {
	exml::Element myElement("NodeName");
	exml::Element myOtherElement = myElement;
	//EXPECT_EQ(myElement, myOtherElement);
}


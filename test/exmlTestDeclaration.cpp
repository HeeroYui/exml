/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <gtest/gtest.h>
#include <exml/exml.hpp>
#include <exml/Declaration.hpp>

TEST(TestDeclaration, create) {
	exml::Declaration myDeclaration("type");
	EXPECT_EQ(myDeclaration.getType(), exml::nodeType::declaration);
}

TEST(TestDeclaration, createCopy) {
	exml::Declaration myDeclaration("type");
	exml::Declaration myOtherDeclaration(myDeclaration);
	//EXPECT_EQ(myDeclaration, myOtherDeclaration);
}

TEST(TestDeclaration, createAssignement) {
	exml::Declaration myDeclaration("type");
	exml::Declaration myOtherDeclaration;
	myOtherDeclaration = myDeclaration;
	//EXPECT_EQ(myDeclaration, myOtherDeclaration);
}


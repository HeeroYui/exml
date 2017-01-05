/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <gtest/gtest.h>
#include <exml/exml.hpp>
#include <exml/Comment.hpp>

TEST(TestComment, create) {
	exml::Comment myComment("my Comment");
	EXPECT_EQ(myComment.getType(), exml::nodeType::comment);
}

TEST(TestComment, createCopy) {
	exml::Comment myComment("my Comment");
	exml::Comment myOtherComment(myComment);
	//EXPECT_EQ(myComment, myOtherComment);
}

TEST(TestComment, createAssignement) {
	exml::Comment myComment("my comment");
	exml::Comment myOtherComment;
	myOtherComment = myComment;
	//EXPECT_EQ(myComment, myOtherComment);
}

TEST(TestComment, transform) {
	exml::Comment myComment("my comment");
	exml::Node myNode = myComment;
	myComment = myNode.toComment();
	//EXPECT_EQ(myComment, myOtherComment);
}

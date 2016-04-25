/** @file
 * @author Edouard DUPIN
 * @copyright 2014, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */

#include <etk/types.h>
#include <test-debug/debug.h>
#include <exml/exml.h>
#include <gtest/gtest.h>

// _errorPos : -1 : no error , 1 : parsing error, 2 generation error, 3 comparaison error ????
void exmlLocalTest(const std::string& _ref,
                   const std::string& _input,
                   int32_t _errorPos,
                   bool _caseInSensitive=false) {
	exml::Document doc;
	//doc.setCaseSensitive(!_caseInSensitive);
	//EXML_DEBUG("parse : \n" << l_list[iii].m_input);
	bool retParse = doc.parse(_input);
	if (_errorPos == 1) {
		EXPECT_EQ(retParse, false);
		return;
	} else {
		EXPECT_EQ(retParse, true);
	}
	std::string out("");
	bool retGenerate = doc.generate(out);
	if (_errorPos == 2) {
		EXPECT_EQ(retGenerate, false);
		return;
	} else {
		EXPECT_EQ(retGenerate, true);
	}
	if (_errorPos == 3) {
		EXPECT_NE(_ref, out);
		return;
	} else {
		EXPECT_EQ(_ref, out);
	}
}


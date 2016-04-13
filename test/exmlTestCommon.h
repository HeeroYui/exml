/** @file
 * @author Edouard DUPIN
 * 
 * @copyright 2014, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.h>

// _errorPos : -1 : no error , 1 : parsing error, 2 generation error, 3 comparaison error ????
void exmlLocalTest(const std::string& _ref,
                   const std::string& _input,
                   int32_t _errorPos,
                   bool _caseInSensitive=false);


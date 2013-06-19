/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license BSD v3 (see license file)
 */

#ifndef __EXML_DEBUG_H__
#define __EXML_DEBUG_H__

#include <etk/types.h>
#include <etk/Debug.h>

extern const char * g_exmlLibName;

#define EXML_CRITICAL(data)			ETK_CRITICAL(g_exmlLibName, data)
#define EXML_WARNING(data)			ETK_WARNING(g_exmlLibName, data)
#define EXML_ERROR(data)			ETK_ERROR(g_exmlLibName, data)
#define EXML_INFO(data)				ETK_INFO(g_exmlLibName, data)
#define EXML_DEBUG(data)			ETK_DEBUG(g_exmlLibName, data)
#define EXML_VERBOSE(data)			ETK_VERBOSE(g_exmlLibName, data)
#define EXML_ASSERT(cond, data)		ETK_ASSERT(g_exmlLibName, cond, data)
#define EXML_CHECK_INOUT(cond)		ETK_CHECK_INOUT(g_exmlLibName, cond)
#define EXML_TODO(cond)				ETK_TODO(g_exmlLibName, cond)

#endif


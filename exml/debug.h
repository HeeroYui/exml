/**
 * @author Edouard DUPIN
 * 
 * @copyright 2011, Edouard DUPIN, all right reserved
 * 
 * @license APACHE v2.0 (see license file)
 */

#ifndef __EXML_DEBUG_H__
#define __EXML_DEBUG_H__

#include <etk/log.h>

namespace exml {
	int32_t getLogId();
};
// TODO : Review this problem of multiple intanciation of "std::stringbuf sb"
#define EXML_BASE(info,data) \
	do { \
		if (info <= etk::log::getLevel(exml::getLogId())) { \
			std::stringbuf sb; \
			std::ostream tmpStream(&sb); \
			tmpStream << data; \
			etk::log::logStream(exml::getLogId(), info, __LINE__, __class__, __func__, tmpStream); \
		} \
	} while(0)

#define EXML_CRITICAL(data)      EXML_BASE(1, data)
#define EXML_ERROR(data)         EXML_BASE(2, data)
#define EXML_WARNING(data)       EXML_BASE(3, data)
#ifdef DEBUG
	#define EXML_INFO(data)          EXML_BASE(4, data)
	#define EXML_DEBUG(data)         EXML_BASE(5, data)
	#define EXML_VERBOSE(data)       EXML_BASE(6, data)
	#define EXML_TODO(data)          EXML_BASE(4, "TODO : " << data)
#else
	#define EXML_INFO(data)          do { } while(false)
	#define EXML_DEBUG(data)         do { } while(false)
	#define EXML_VERBOSE(data)       do { } while(false)
	#define EXML_TODO(data)          do { } while(false)
#endif

#define EXML_ASSERT(cond,data) \
	do { \
		if (!(cond)) { \
			EXML_CRITICAL(data); \
			assert(!#cond); \
		} \
	} while (0)

#endif


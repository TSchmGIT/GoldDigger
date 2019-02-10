#pragma once

#ifdef USE_ASSERTS
#include "AssertManager.h"

#define ASSERT(condition)										if (!(condition)){ hvsdk::CAssertManager::CreateErrorAssert(#condition); LOG_ERROR("ASSERT: " << #condition);}
#define ASSERT_TEXT(condition, message)							if (!(condition)){ hvsdk::CAssertManager::CreateErrorAssert(#condition); LOG_ERROR("ASSERT: " << message);}
#define ASSERT_OR_EXECUTE(condition, statement)					if (!(condition)){ hvsdk::CAssertManager::CreateErrorAssert(#condition); LOG_ERROR("ASSERT: " << #condition);	statement;}
#define ASSERT_OR_EXECUTE_TEXT(condition, message, statement)	if (!(condition)){ hvsdk::CAssertManager::CreateErrorAssert(#condition); LOG_ERROR("ASSERT: " << message);		statement;}
#else // !USE_ASSERTS
#define ASSERT(condition)										__noop;
#define ASSERT_TEXT(condition, message)							__noop;
#define ASSERT_OR_EXECUTE(condition, statement)					__noop;
#define ASSERT_OR_EXECUTE_TEXT(condition, message, statement)	__noop;
#endif // USE_ASSERTS
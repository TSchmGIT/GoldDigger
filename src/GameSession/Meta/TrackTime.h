#pragma once

#define TT_BEGIN(key)	CPerformanceManager::GetMutable().StartTracking(key);
#define TT_END(key)		CPerformanceManager::GetMutable().StopTracking(key);
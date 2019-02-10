#include "stdafx.h"
#include "PerformanceManager.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CPerformanceManager::CPerformanceManager()
{

}

//////////////////////////////////////////////////////////////////////////

CPerformanceManager::~CPerformanceManager()
{

}

//////////////////////////////////////////////////////////////////////////

void CPerformanceManager::Init()
{
	m_TrackingMap.clear();
}

//////////////////////////////////////////////////////////////////////////

void CPerformanceManager::StartTracking(String key)
{
	ASSERT_OR_EXECUTE_TEXT(m_TrackingMap.find(key) == m_TrackingMap.end(), "Started tracking with the key " << key << "more than once! Ignoring additional tracking", return);
	m_TrackingMap.emplace(key, std::chrono::steady_clock::now());
}

//////////////////////////////////////////////////////////////////////////

void CPerformanceManager::StopTracking(String key)
{
	ASSERT_OR_EXECUTE_TEXT(m_TrackingMap.find(key) != m_TrackingMap.end(), "Stopped tracking with the unknown key " << key << "! Could not resolve tracking", return);

	DurationMS durationMS = std::chrono::steady_clock::now() - m_TrackingMap[key];

	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << durationMS.count();
	LOG_INFO("PERF: Operation " << key << " took " << ss.str() << " ms");

	m_TrackingMap.erase(key);
}

//////////////////////////////////////////////////////////////////////////

} // hvgs

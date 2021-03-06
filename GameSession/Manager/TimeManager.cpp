#include "stdafx.h"
#include "TimeManager.h"
#include <chrono>

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CTimeManager::CTimeManager()
{

}

//////////////////////////////////////////////////////////////////////////

CTimeManager::~CTimeManager()
{

}

//////////////////////////////////////////////////////////////////////////

void CTimeManager::Init()
{
	m_GameTime = 0.0f;
	m_GameTimeDelta = 0.0f;

	m_AppTime = 0.0f;
	m_AppTimeDelta = 0.0f;

	m_LastTickTimestamp = std::chrono::steady_clock::now();
	m_FrameCount = 0;
}

//////////////////////////////////////////////////////////////////////////

void CTimeManager::PrepareTick()
{
	// Calculate exact delta
	TimePoint now = std::chrono::steady_clock::now();
	DurationMS deltaMS = now - m_LastTickTimestamp;
	float deltaSec = deltaMS.count() / 1000.0f;

	// Assign delta values
	m_GameTimeDelta = deltaSec;
	m_AppTimeDelta = deltaSec;

	// Apply delta values
	m_GameTime += m_GameTimeDelta;
	m_AppTime += m_AppTimeDelta;

	// Set last tick timestamp
	m_LastTickTimestamp = now;

	// Increase frame count
	m_FrameCount++;
}

//////////////////////////////////////////////////////////////////////////

GameTime CTimeManager::GetGameTime() const
{
	return m_GameTime;
}

//////////////////////////////////////////////////////////////////////////

GameTime CTimeManager::GetGameDeltaTime() const
{
	return m_GameTimeDelta;
}

//////////////////////////////////////////////////////////////////////////

AppTime CTimeManager::GetAppTime() const
{
	return m_AppTime;
}

//////////////////////////////////////////////////////////////////////////

AppTime CTimeManager::GetAppDeltaTime() const
{
	return m_AppTimeDelta;
}

//////////////////////////////////////////////////////////////////////////

int CTimeManager::GetFrameCount() const
{
	return m_FrameCount;
}

//////////////////////////////////////////////////////////////////////////

float CTimeManager::GetFPS() const
{
	return 1.0f / m_AppTimeDelta;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs

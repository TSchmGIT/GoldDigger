#pragma once

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CTimeManager : public CSingletonBase<CTimeManager>
{

public:
	CTimeManager();
	virtual ~CTimeManager();

public:
	void Init();

	void PrepareTick();

public:
	GameTime GetGameTime() const;
	GameTime GetGameDeltaTime() const;
	AppTime GetAppTime() const;
	AppTime GetAppDeltaTime() const;

	int GetFrameCount() const;
	float GetFPS() const;
	float GetFPSAverage() const;

protected:
	int			m_FrameCount = 0;

	TimePoint	m_LastTickTimestamp;

	GameTime	m_GameTime = 0;
	AppTime		m_AppTime = 0;

	GameTime	m_GameTimeDelta = 0;
	AppTime		m_AppTimeDelta = 0;

protected:
	float			m_AverageFps = 0.0f;
	Vector<float>	m_AverageFpsList;
	float			m_AverageFpsTimestamp = 0.0f;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

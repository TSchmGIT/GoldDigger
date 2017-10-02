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
	AppTime GetAppTime() const;

	int GetFrameCount() const;
	float GetFPS() const;

protected:
	int			m_FrameCount;

	TimePoint	m_LastTickTimestamp;

	GameTime	m_GameTime;
	AppTime		m_AppTime;
	
	GameTime	m_GameTimeDelta;
	AppTime		m_AppTimeDelta;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

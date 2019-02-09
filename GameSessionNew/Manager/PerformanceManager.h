#pragma once
#include "GameSessionNew/Manager/SingletonBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CPerformanceManager : public CSingletonBase<CPerformanceManager>
{

public:
	CPerformanceManager();
	virtual ~CPerformanceManager();

	void Init();

public:
	void StartTracking(String key);
	void StopTracking(String key);

protected:
	Map<String, TimePoint> m_TrackingMap;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs


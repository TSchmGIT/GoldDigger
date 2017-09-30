#pragma once
#include "GameSession/Manager/SingletonBase.h"

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

	void StartTrackingNew(String key);
	void StopTrackingNew();

protected:
	Map<String, TimePoint> m_TrackingMap;
	UniquePtr<CTrackItem> m_TrackItem;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs


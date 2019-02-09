#pragma once
#include "GameSessionNew/Manager/SingletonBase.h"

/////////////////////////////////////////////////////////////////////////////
namespace hvgs
{
class CCamera;
}

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CCameraManager : public CSingletonBase<CCameraManager>
{

public:
	CCameraManager();
	virtual ~CCameraManager();

	void Init();

	void Tick();

public:
	const CCamera* GetActive() const;
	CCamera* GetActive();

protected:
	CCamera* m_ActiveCamera;
	Vector<CCamera> m_CameraList;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

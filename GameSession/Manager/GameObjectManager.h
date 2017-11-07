#pragma once
#include "GameSession/Manager/SingletonBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class IGameObject;
}

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CGameObjectManager : public CSingletonBase<CGameObjectManager>
{

public:
	CGameObjectManager();
	virtual ~CGameObjectManager();

public:
	void RegisterGameObject(IGameObject* gameObject);
	void UnregisterGameObject(IGameObject* gameObject);

public:
	void PrepareTick();
	void Tick();

protected:
	Vector<IGameObject*> m_GameObjectList;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

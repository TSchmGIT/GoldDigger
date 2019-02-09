#include "stdafx.h"
#include "GameObjectManager.h"

#include "GameSessionNew/GameObjects/IGameObject.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CGameObjectManager::CGameObjectManager()
{
	m_GameObjectList.reserve(1000);
}

//////////////////////////////////////////////////////////////////////////

CGameObjectManager::~CGameObjectManager()
{

}

//////////////////////////////////////////////////////////////////////////

void CGameObjectManager::RegisterGameObject(IGameObject* gameObject)
{
	ASSERT_OR_EXECUTE(gameObject, return);

#if _DEBUG
	auto it = std::find_if(m_GameObjectList.begin(), m_GameObjectList.end(), [gameObject](const IGameObject* element) { return gameObject == element; });
	ASSERT_OR_EXECUTE(it == m_GameObjectList.end(), return);
#endif

	m_GameObjectList.push_back(gameObject);
}

//////////////////////////////////////////////////////////////////////////

void CGameObjectManager::UnregisterGameObject(IGameObject* gameObject)
{
	ASSERT_OR_EXECUTE(gameObject, return);

	auto it = std::find_if(m_GameObjectList.begin(), m_GameObjectList.end(), [gameObject](const IGameObject* element) { return gameObject == element; });
	ASSERT_OR_EXECUTE(it != m_GameObjectList.end(), return);

	m_GameObjectList.erase(it);
}

//////////////////////////////////////////////////////////////////////////

void CGameObjectManager::PrepareTick()
{
	for (IGameObject* gameObject : m_GameObjectList)
	{
		gameObject->PrepareTick();
	}
}

//////////////////////////////////////////////////////////////////////////

void CGameObjectManager::Tick()
{
	for (IGameObject* gameObject : m_GameObjectList)
	{
		gameObject->Tick();
	}
}

//////////////////////////////////////////////////////////////////////////

void CGameObjectManager::InitAfterCreation()
{
	for (auto* gameObject : m_GameObjectList)
	{
		gameObject->InitAfterCreation();
	}
}

//////////////////////////////////////////////////////////////////////////

} // hvgs

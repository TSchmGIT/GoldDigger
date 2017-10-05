#include "stdafx.h"
#include "GameObjectManager.h"

#include "GameSession/GameObjects/IGameObject.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CGameObjectManager::CGameObjectManager()
{

}

//////////////////////////////////////////////////////////////////////////

CGameObjectManager::~CGameObjectManager()
{

}

//////////////////////////////////////////////////////////////////////////

void CGameObjectManager::RegisterGameObject(IGameObject* gameObject)
{
	ASSERT_OR_EXECUTE(gameObject, return);

	auto it = std::find_if(m_GameObjectList.begin(), m_GameObjectList.end(), [gameObject](IGameObject* element) { return gameObject == element; });
	ASSERT_OR_EXECUTE(it == m_GameObjectList.end(), return);
	
	m_GameObjectList.push_back(gameObject);
}

//////////////////////////////////////////////////////////////////////////

void CGameObjectManager::UnregisterGameObject(IGameObject* gameObject)
{
	ASSERT_OR_EXECUTE(gameObject, return);

	auto it = std::find_if(m_GameObjectList.begin(), m_GameObjectList.end(), [gameObject](IGameObject* element) { return gameObject == element; });
	ASSERT_OR_EXECUTE(it != m_GameObjectList.end(), return);

	m_GameObjectList.erase(it);
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

} // hvgs

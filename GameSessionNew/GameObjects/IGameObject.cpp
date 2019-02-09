#include "stdafx.h"
#include "IGameObject.h"

#include "GameSessionNew/Manager/GameObjectManager.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

IGameObject::IGameObject()
{
	CGameObjectManager::GetMutable().RegisterGameObject(this);
}

//////////////////////////////////////////////////////////////////////////

IGameObject::IGameObject(const IGameObject&)
{
	CGameObjectManager::GetMutable().RegisterGameObject(this);
}

//////////////////////////////////////////////////////////////////////////

IGameObject::IGameObject(IGameObject&&)
{
	CGameObjectManager::GetMutable().RegisterGameObject(this);
}

//////////////////////////////////////////////////////////////////////////

IGameObject& IGameObject::operator=(const IGameObject&)
{
	ASSERT_TEXT(false, "No implementation for method IGameObject::operator=(const IGameObject& other)");
	return *this;
}

//////////////////////////////////////////////////////////////////////////

IGameObject& IGameObject::operator=(IGameObject&&)
{
	ASSERT_TEXT(false, "No implementation for method IGameObject::operator=(IGameObject&& other)");
	return *this;
}

//////////////////////////////////////////////////////////////////////////

IGameObject::~IGameObject()
{
	CGameObjectManager::GetMutable().UnregisterGameObject(this);
}

//////////////////////////////////////////////////////////////////////////

} // hvgs

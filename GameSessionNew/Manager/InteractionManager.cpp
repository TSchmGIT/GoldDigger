#include "stdafx.h"
#include "InteractionManager.h"

#include "GameSessionNew/Actor/Interaction/IInteractionObject.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CInteractionManager::CInteractionManager()
{

}

//////////////////////////////////////////////////////////////////////////

CInteractionManager::~CInteractionManager()
{

}

//////////////////////////////////////////////////////////////////////////

void CInteractionManager::Tick()
{
	for (auto* interactionObject : m_InteractionObjectSet)
	{
		interactionObject->Tick();
	}
}

//////////////////////////////////////////////////////////////////////////

void CInteractionManager::Draw() const
{
	for (auto* interactionObject : m_InteractionObjectSet)
	{
		interactionObject->Draw();
	}
}

//////////////////////////////////////////////////////////////////////////

void CInteractionManager::RegisterInteractionObject(IInteractionObject* interactionObject)
{
	ASSERT_OR_EXECUTE(interactionObject, return);

#if _DEBUG
	//auto it = std::find_if(m_InteractionObjectSet.begin(), m_InteractionObjectSet.end(), [collisionObject](const ICollisionObject* element) { return element == collisionObject; });
	auto it = m_InteractionObjectSet.find(interactionObject);
	ASSERT_OR_EXECUTE(it == m_InteractionObjectSet.end(), return);
#endif

	m_InteractionObjectSet.emplace(interactionObject);
}

//////////////////////////////////////////////////////////////////////////

void CInteractionManager::UnregisterInteractionObject(IInteractionObject* interactionObject)
{
	ASSERT_OR_EXECUTE(interactionObject, return);

	//auto it = std::find_if(m_InteractionObjectSet.begin(), m_InteractionObjectSet.end(), [collisionObject](const ICollisionObject* element) { return element == collisionObject; });
	auto it = m_InteractionObjectSet.find(interactionObject);
	ASSERT_OR_EXECUTE(it != m_InteractionObjectSet.end(), return);

	m_InteractionObjectSet.erase(it);
}

//////////////////////////////////////////////////////////////////////////

const hvgs::Set<IInteractionObject*>& CInteractionManager::GetInteractionObjects() const
{
	return m_InteractionObjectSet;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs

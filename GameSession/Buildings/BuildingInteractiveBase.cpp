#include "stdafx.h"
#include "BuildingInteractiveBase.h"

#include "GameSession/UI/Scenes/Meta/SceneManager.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

bool CBuildingInteractiveBase::IsInInteractionDistance(const WorldPos& position) const
{
	return Vector2::DistanceCheck(position, GetPosition(), m_InteractionDistance);
}

//////////////////////////////////////////////////////////////////////////

void CBuildingInteractiveBase::StartInteraction()
{
	ui::CSceneManager::GetMutable().EnterState(GetUISceneID());
}

//////////////////////////////////////////////////////////////////////////

void CBuildingInteractiveBase::StopInteraction()
{
	ui::CSceneManager::GetMutable().LeaveState(GetUISceneID());
}

//////////////////////////////////////////////////////////////////////////

hvgs::WorldPos CBuildingInteractiveBase::GetInteractionButtonPosition() const
{
	return GetPosition() + WorldPos(0.0f, GetAABBHalfs().y);
}

//////////////////////////////////////////////////////////////////////////

const hvgs::WorldPos& CBuildingInteractiveBase::GetInteractionOriginPosition() const
{
	return GetPosition();
}

} // hvgs

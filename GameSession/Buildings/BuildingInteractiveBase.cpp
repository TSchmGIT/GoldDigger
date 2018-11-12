#include "stdafx.h"
#include "BuildingInteractiveBase.h"

#include "GameSession/UI/Scenes/Meta/SceneManager.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

bool CBuildingInteractiveBase::IsInInteractionDistance(const WorldPos& position) const
{
	return Vector2::DistanceCheck(position, m_Position, m_InteractionDistance);
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
	return m_Position + WorldPos(0.0f, GetAABBHalfs().y);
}

//////////////////////////////////////////////////////////////////////////

const hvgs::WorldPos& CBuildingInteractiveBase::GetInteractionOriginPosition() const
{
	return m_Position;
}

} // hvgs

#include "stdafx.h"
#include "MotorDigging.h"

#include "GameSessionNew/Actor/Actor.h"
#include "GameSessionNew/Items/Inventory.h"
#include "GameSessionNew/Items/ItemBlock.h"
#include "GameSessionNew/Manager/TimeManager.h"
#include "GameSessionNew/World/Tile.h"
#include "GameSessionNew/World/World.h"
#include "../Equipment/Modules/EnumsModules.h"
#include "../Equipment/Equipment.h"
#include "../Equipment/Modules/ModuleFuelTank.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CMotorDigging::CMotorDigging(const CMotorBase& other)
	: CMotorBase(other)
{

}

//////////////////////////////////////////////////////////////////////////

const hvgs::WorldPos& CMotorDigging::GetTargetPosition() const
{
	return m_TargetPos;
}

//////////////////////////////////////////////////////////////////////////

void CMotorDigging::SetTargetPosition(const WorldPos& worldPos)
{
	m_TargetPos = worldPos;
}

//////////////////////////////////////////////////////////////////////////

float CMotorDigging::GetDiggingPower() const
{
	return m_DiggingPower;
}

//////////////////////////////////////////////////////////////////////////

void CMotorDigging::Tick()
{
	CMotorBase::Tick(); // Base call

	
	if (auto* moduleFuelTank = m_Actor.GetEquipment().GetModule<CModuleFuelTank>(); moduleFuelTank)
	{
		moduleFuelTank->SetFuelPenalty(FuelPenalty::Digging, true);
	}

	// Move towards target
	WorldPos newPos = Vector2::MoveTowards(m_Actor.GetPosition(), m_TargetPos, m_DiggingPower * CTimeManager::Get().GetGameDeltaTime());
	m_Actor.SetPosition(newPos);

	// Check if close to target and end digging
	if (Vector2::SqrMagnitude(newPos - m_TargetPos) < 0.025f * 0.025f) // 0.025f distance to target as threshold
	{
		ProcessTileDigging(); // Destroys tile and grants item

		// remove fuel penalty
		if (auto* moduleFuelTank = m_Actor.GetEquipment().GetModule<CModuleFuelTank>(); moduleFuelTank)
		{
			moduleFuelTank->SetFuelPenalty(FuelPenalty::Digging, false);
		}

		// Stop digging motor
		m_Actor.StopDigging();
		return;
	}
}

//////////////////////////////////////////////////////////////////////////

void CMotorDigging::ProcessTileDigging()
{
	// Get tile that should be mined
	Optional<const CTile&> tile = CWorld::Get().GetTileAt(m_TargetPos);
	ASSERT_OR_EXECUTE_TEXT(tile, "Tried to mine tile that is not available", return);
	TileType tileType = tile->GetTileType();

	// Destroy tile
	CWorld::GetMutable().SetTileAt(m_TargetPos, TileType::Air);

	// Collect resource dropped
	m_Actor.GetInventory().AddItem(std::make_unique<CItemBlock>(tileType));

	// Notify actor to stop digging
}

//////////////////////////////////////////////////////////////////////////

void CMotorDigging::SetDiggingPower(float diggingPower)
{
	m_DiggingPower = diggingPower;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs

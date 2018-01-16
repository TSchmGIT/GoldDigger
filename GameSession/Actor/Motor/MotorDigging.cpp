#include "stdafx.h"
#include "MotorDigging.h"

#include "GameSession/Actor/Actor.h"
#include "GameSession/Items/Inventory.h"
#include "GameSession/Items/ItemBlock.h"
#include "GameSession/Manager/TimeManager.h"
#include "GameSession/World/Tile.h"
#include "GameSession/World/World.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CMotorDigging::CMotorDigging(const CMotorBase& other)
	: CMotorBase(other)
{

}

//////////////////////////////////////////////////////////////////////////

CMotorDigging::CMotorDigging(const CMotorDigging& other)
	: CMotorBase(other)
	, m_TargetPos(other.m_TargetPos)
{
}

//////////////////////////////////////////////////////////////////////////

CMotorDigging::~CMotorDigging()
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

	// Move towards target
	WorldPos newPos = Vector2::MoveTowards(m_Actor->GetPosition(), m_TargetPos, m_DiggingPower * CTimeManager::Get().GetGameDeltaTime());
	m_Actor->SetPosition(newPos);

	// Check if close to target and end digging
	if (Vector2::SqrMagnitude(newPos - m_TargetPos) < 0.025f * 0.025f) // 0.025f distance to target as threshold
	{
		ProcessTileDigging(); // Destorys tile and grants item

		// Stop digging motor
		m_Actor->StopDigging();
		return;
	}
}

//////////////////////////////////////////////////////////////////////////

void CMotorDigging::ProcessTileDigging()
{
	// Get tile that should be mined
	const CTile* tile = CWorld::GetMutable()->GetTileAt(m_TargetPos);
	ASSERT_OR_EXECUTE_TEXT(tile, "Tried to mine tile that is not available", return);
	TileType tileType = tile->GetTileType();

	// Destroy tile
	CWorld::GetMutable()->SetTileAt(m_TargetPos, TileType::Air);

	// Collect resource dropped
	m_Actor->GetInventory().AddItem(std::make_unique<CItemBlock>(tileType));

	// Notify actor to stop digging
}

//////////////////////////////////////////////////////////////////////////

void CMotorDigging::SetDiggingPower(float diggingPower)
{
	m_DiggingPower = diggingPower;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs

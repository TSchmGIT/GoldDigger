#include "stdafx.h"
#include "Actor.h"

#include <hvmath/Physics/AABB.h>

#include "GameSession/Camera/Camera.h"
#include "GameSession/Items/Inventory.h"
#include "GameSession/Items/ItemBlock.h"
#include "GameSession/Manager/CameraManager.h"
#include "GameSession/Manager/InputManager.h"
#include "GameSession/Manager/PhysicsManager.h"
#include "GameSession/Manager/RenderManager.h"
#include "GameSession/Manager/TimeManager.h"
#include "GameSession/Physics/PhysicsEnums.h"
#include "GameSession/Rendering/DebugRender.h"
#include "GameSession/Rendering/Textures/EnumsTexture.h"
#include "GameSession/World/World.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

const float MOVEMENT_SPEED = 5.0f;

////////////////////////////////////////////////////////////////////////////

CActor::CActor()
	: m_Position()
{
}

//////////////////////////////////////////////////////////////////////////

CActor::CActor(const CActor& other)
{
	if (other.m_Inventory)
	{
		m_Inventory = std::make_unique<CInventory>(*other.m_Inventory);
	}
}

//////////////////////////////////////////////////////////////////////////

CActor::~CActor()
{

}

//////////////////////////////////////////////////////////////////////////

void CActor::Tick()
{
	Vector2 deltaMovement;
	ProcessMovement(deltaMovement);

	// Collect tiles
	if (CInputManager::Get().IsMouseButtonDown(MouseButton::Left))
	{
		CCamera* cam = CCameraManager::GetMutable().GetActive();
		ASSERT_OR_EXECUTE(cam, return);

		auto&& tile = CWorld::GetWorld()->GetTileAt(cam->ScreenToWorldPoint(CInputManager::Get().GetMousePos()));

		if (tile && tile->GetTileType() != TileType::Air)
		{
			m_Inventory->AddItem(std::make_unique<CItemBlock>(tile->GetTileType()));

			CWorld::GetWorld()->SetTileAt(cam->ScreenToWorldPoint(CInputManager::Get().GetMousePos()), TileType::Air, false);
		}
	}

	// Place tiles
	if (CInputManager::Get().IsMouseButtonDown(MouseButton::Right) && m_Inventory->HasItems())
	{
		CCamera* cam = CCameraManager::GetMutable().GetActive();
		ASSERT_OR_EXECUTE(cam, return);

		auto&& item = m_Inventory->GetItemAt(0);
		auto&& itemBlock = dynamic_cast<const CItemBlock*>(item);
		if (itemBlock)
		{
			CWorld::GetWorld()->SetTileAt(cam->ScreenToWorldPoint(CInputManager::Get().GetMousePos()), itemBlock->GetTileType(), false);

			m_Inventory->RemoveItemAt(0);
		}
	}

	UpdateCamera(deltaMovement);
}

//////////////////////////////////////////////////////////////////////////

void CActor::Draw() const
{
	CRenderManager::GetMutable().DrawSpriteWorld(m_Position, TextureName::Actor, Alignment::CenterBottom);

	// Debug
	std::ostringstream ss;
	ss << "(" << m_Position.x << ", " << m_Position.y << ")";
	CRenderManager::GetMutable().DrawTextWorld(m_Position, ss.str(), FontName::Courier_New, 30);

	DebugRender::DrawRect(CRenderManager::GetMutable().GetWindow(), { GetAABBOrigin(), GetAABBHalfs() });
}

//////////////////////////////////////////////////////////////////////////

hvgs::WorldPos CActor::GetPosition() const
{
	return m_Position;
}

//////////////////////////////////////////////////////////////////////////

void CActor::SetPosition(const WorldPos& position)
{
	if (m_Position == position)
	{
		return;
	}

	m_Position = position;
}

//////////////////////////////////////////////////////////////////////////

const hvgs::CInventory* CActor::GetInventory() const
{
	return m_Inventory.get();
}

//////////////////////////////////////////////////////////////////////////

void CActor::ProcessMovement(Vector2& deltaMovement)
{
	// Update AABB
	m_AABB.pos = GetAABBOrigin();
	m_AABB.half = GetAABBHalfs();

	// Get Input
	float hor = CInputManager::Get().GetAxis(Axis::Horizontal);
	float ver = CInputManager::Get().GetAxis(Axis::Vertical);

	// Calculate delta movement
	deltaMovement = Vector2(hor, ver).Normalize() * MOVEMENT_SPEED * CTimeManager::Get().GetGameDeltaTime();

	// Return if there is no movement to be calculated
	if (deltaMovement.x == 0.0f && deltaMovement.y == 0.0f)
	{
		return;
	}

	Vector2 oldAABBPos = GetAABBOrigin();
	Vector2 oldDelta = deltaMovement;
	Vector2 newAABBPos;
	Vector2 newDelta;

	int iteration = 0;
	while (iteration < 100)
	{
		bool collisionSweep = PerformSingleSweep(oldAABBPos, GetAABBHalfs(), oldDelta, newAABBPos, newDelta);

		oldAABBPos = newAABBPos;
		oldDelta = newDelta;

		// Break if no collision occurred
		// Or if the resulting delta vector is zero (no further movement possible)
		if (!collisionSweep || (oldDelta.x == 0.0f && oldDelta.y == 0.0f))
		{
			break;
		}

		iteration++;
	}

	Vector2 newPos = newAABBPos - GetAABBOriginOffset();
	deltaMovement = newPos - m_Position;
	m_Position = newPos;

}

//////////////////////////////////////////////////////////////////////////

void CActor::UpdateCamera(const Vector2& deltaMovement) const
{
	// Update camera
	CCamera* cam = CCameraManager::GetMutable().GetActive();
	ASSERT_OR_EXECUTE(cam, return);

	cam->SetPosition(cam->GetPosition() + deltaMovement);
}

//////////////////////////////////////////////////////////////////////////

bool CActor::PerformSingleSweep(const Vector2& pos, const Vector2& halfs, const Vector2& delta, Vector2& newPos, Vector2& newDelta) const
{
	//Construct aabb for sweep test
	hvmath::AABB aabb(pos, halfs);

	// Prepare result values
	hvmath::AABB collider;
	hvmath::Sweep sweep;

	bool collided = CPhysicsManager::Get().SweepTest(aabb, delta, Layer::Environment, sweep, collider);

	if (!collided)
	{
		newPos = pos + delta;
		newDelta = { 0.0f, 0.0f };

		// No collision occurred
		return false;
	}
	else
	{
		// Move forward up to the point of collision
		newPos = pos + delta * sweep.time + sweep.hit.normal * 0.001f; // Minimal offset to a surface (epsilon);

		// Calculate the new moving direction depending of the hit normal
		newDelta = Vector2::Normalize(delta - sweep.hit.normal * Vector2::Dot(sweep.hit.normal, delta));

		// Calculate the missing movement in the new direction
		newDelta *= (1.0f - sweep.time) * Vector2::Magnitude(delta);

		return true;
	}
}

//////////////////////////////////////////////////////////////////////////

inline hvgs::WorldPos CActor::GetAABBOrigin() const
{
	return m_Position + GetAABBOriginOffset();
}

//////////////////////////////////////////////////////////////////////////

inline hvgs::WorldPos CActor::GetAABBHalfs() const
{
	return{ 0.45f, 0.45f }; // In world coords
}

//////////////////////////////////////////////////////////////////////////

inline hvgs::WorldPos CActor::GetAABBOriginOffset() const
{
	return{ 0.0f, GetAABBHalfs().y };
}

//////////////////////////////////////////////////////////////////////////

inline Layer CActor::GetLayer() const
{
	return Layer::Actor;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs

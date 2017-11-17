#include "stdafx.h"
#include "MotorDefault.h"

#include <hvmath/Physics/AABB.h>

#include "GameSession/Actor/Actor.h"
#include "GameSession/Manager/InputManager.h"
#include "GameSession/Manager/PhysicsManager.h"
#include "GameSession/Manager/TimeManager.h"
#include "GameSession/Physics/PhysicsEnums.h"
#include "GameSession/World/Tile.h"
#include "GameSession/World/World.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

const float ACCELERATION_FORCE = 20.0f;


//////////////////////////////////////////////////////////////////////////

CMotorDefault::CMotorDefault(CActor* actor)
	: CMotorBase(actor)
{

}

//////////////////////////////////////////////////////////////////////////

CMotorDefault::CMotorDefault(const CMotorDefault& other)
	: CMotorBase::CMotorBase(other)
	, m_GravityVelocity(other.m_GravityVelocity)
	, m_IsGrounded(other.m_IsGrounded)
{

}

//////////////////////////////////////////////////////////////////////////

CMotorDefault::CMotorDefault(const CMotorBase& other)
	: CMotorBase(other)
{

}

//////////////////////////////////////////////////////////////////////////

CMotorDefault::~CMotorDefault()
{

}

//////////////////////////////////////////////////////////////////////////

void CMotorDefault::Tick()
{
	CMotorBase::Tick(); // Base call

	// Update gravity velocity
	UpdateGravityVelocity();

	// Reset velocity

	// Update AABB
	const hvmath::AABB& aabb = m_Actor->GetAABB();

	// Get Input
	float hor = CInputManager::Get().GetAxis(Axis::Horizontal);
	float ver = CInputManager::Get().GetButton(Button::Jump) ? 1.0f : 0.0f;

	// Calculate delta movement
	Vector2 acceleration = Vector2(hor, ver).Normalize() * ACCELERATION_FORCE;
	if (!m_IsGrounded)
	{
		m_Velocity += CPhysicsManager::Get().GetGravity() * CTimeManager::Get().GetGameDeltaTime();
	}
	else
	{
		m_Velocity += Vector2{ 0.0f, -0.1f };
	}

	m_Velocity += acceleration * CTimeManager::Get().GetGameDeltaTime();
	m_Velocity *= (1.0f - 0.45f * CTimeManager::Get().GetGameDeltaTime());

	Vector2 deltaMovement = m_Velocity * CTimeManager::Get().GetGameDeltaTime();

	// Return if there is no movement to be calculated
	if (deltaMovement.x == 0.0f && deltaMovement.y == 0.0f)
	{
		return;
	}

	Vector2 oldAABBPos = aabb.pos;
	Vector2 oldDelta = deltaMovement;
	SweepResult sweepResult;

	// At max resolve 10 collisions in a single tick
	int iteration = 0;
	m_IsGrounded = false;
	while (iteration < 10 && (oldDelta.x != 0 || oldDelta.y != 0))
	{
		sweepResult = PerformSingleSweep(oldAABBPos, aabb.half, oldDelta);

		oldAABBPos = sweepResult.newPos;
		oldDelta = sweepResult.newDelta;

		// No collision
		if (sweepResult.flags == CollisionFlags::None)
		{
			break;
		}

		// Collision occured
		m_IsGrounded |= sweepResult.flags == CollisionFlags::Bottom;
		m_Velocity = m_Velocity - sweepResult.sweep.hit.normal * Vector2::Dot(sweepResult.sweep.hit.normal, m_Velocity);

		if (sweepResult.flags == CollisionFlags::Bottom)
		{
			m_GravityVelocity = Vector2(0.0f, 0.0f);
		}

		iteration++;
	}

	// Update position
	Vector2 newPos = sweepResult.newPos - m_Actor->GetAABBOriginOffset();
	deltaMovement = newPos - m_Actor->GetPosition();
	m_Actor->SetPosition(newPos);

	//////////////////////////////////////////////////////////////////////////

	CheckDigging();
}

//////////////////////////////////////////////////////////////////////////

hvgs::SweepResult CMotorDefault::PerformSingleSweep(const Vector2& pos, const Vector2& halfs, const Vector2& delta) const
{
	SweepResult result;

	//Construct aabb for sweep test
	hvmath::AABB aabb(pos, halfs);

	// Prepare result values
	hvmath::AABB collider;

	bool collided = CPhysicsManager::Get().SweepTest(aabb, delta, Layer::Environment, result.sweep, collider);

	if (!collided)
	{
		result.newPos = pos + delta;
		result.newDelta = { 0.0f, 0.0f };
		result.flags = CollisionFlags::None;

		// No collision occurred
		return result;
	}
	else
	{
		// Move forward up to the point of collision
		result.newPos = pos + delta * result.sweep.time + result.sweep.hit.normal * 0.001f; // Minimal offset to a surface (epsilon);

		// Calculate the missing movement in the new direction
		result.newDelta = Vector2::Normalize(delta - result.sweep.hit.normal * Vector2::Dot(result.sweep.hit.normal, delta));
		result.newDelta *= (1.0f - result.sweep.time) * Vector2::Magnitude(delta);

		hvuint8 flags(0);
		if (result.sweep.hit.normal == Vector2(1.0f, 0.0f))
		{
			flags |= hvuint8(CollisionFlags::Right);
		}
		else if (result.sweep.hit.normal == Vector2(-1.0f, 0.0f))
		{
			flags |= hvuint8(CollisionFlags::Left);
		}
		else if (result.sweep.hit.normal == Vector2(0.0f, 1.0f))
		{
			flags |= hvuint8(CollisionFlags::Bottom);
		}
		else if (result.sweep.hit.normal == Vector2(0.0f, -1.0f))
		{
			flags |= hvuint8(CollisionFlags::Top);

		}
		result.flags = CollisionFlags(flags);

		return result;
	}
}

//////////////////////////////////////////////////////////////////////////

void CMotorDefault::UpdateGravityVelocity()
{
	m_GravityVelocity += CPhysicsManager::Get().GetGravity() * CTimeManager::Get().GetGameDeltaTime();
}

//////////////////////////////////////////////////////////////////////////

void CMotorDefault::CheckDigging()
{
	if (!m_IsGrounded)
	{
		return;
	}

	if (Vector2::SqrMagnitude(m_Velocity) > 0.5f * 0.5f)
	{
		return;
	}

	if (!CInputManager::Get().GetButtonDown(Button::Dig))
	{
		return;
	}

	const auto& tile = CWorld::GetWorld()->GetTileAt(m_Actor->GetPosition() + Vector2(0.0f, -1.0f));
	if (!tile || tile->GetTileType() == TileType::Air)
	{
		return;
	}

	m_Actor->StartDigging(*tile);
}

//////////////////////////////////////////////////////////////////////////

} // hvgs

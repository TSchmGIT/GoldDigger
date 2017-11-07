#pragma once

#include <hvmath/Physics/AABB.h>

#include "GameSession/Actor/Motor/MotorBase.h"
#include "GameSession/Physics/PhysicsEnums.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

struct SweepResult
{
	CollisionFlags flags = CollisionFlags::None;
	Vector2 newPos = Vector2(0.0f, 0.0f);
	Vector2 newDelta = Vector2(0.0f, 0.0f);
	hvmath::Sweep sweep;
};

class CMotorDefault : public CMotorBase
{

public:
	CMotorDefault() = default;
	CMotorDefault(CActor* actor);
	virtual ~CMotorDefault();

	virtual void Tick() override;

protected:
	SweepResult PerformSingleSweep(const Vector2& pos, const Vector2& halfs, const Vector2& delta) const;

	void UpdateGravityVelocity();

protected:
	Vector2		m_GravityVelocity;
	bool		m_IsGrounded;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

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
	Vector2 newPos = Vector2();
	Vector2 newDelta = Vector2();
	hvmath::Sweep sweep;
};

class CMotorDefault : public CMotorBase
{

public:
	CMotorDefault() = default;
	CMotorDefault(const CMotorBase& motorBase);
	CMotorDefault(CActor& actor);
	virtual ~CMotorDefault() = default;

	virtual void Tick() override;

protected:
	void ProcessMovementTick();

	SweepResult PerformSingleSweep(const Vector2& pos, const Vector2& halfs, const Vector2& delta) const;

	std::pair<float, float> GetUserInputHorVer() const;

	void UpdateGravityVelocity();
	void CheckDigging();

protected:
	Vector2		m_GravityVelocity = Vector2();
	bool		m_IsGrounded = false;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
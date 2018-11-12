#pragma once

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class CActor;
}

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CMotorBase
{
public:
	CMotorBase() = default;
	CMotorBase(CActor& actor);
	virtual ~CMotorBase();

	virtual void Tick();

	const Vector2& GetVelocity() const;
	void SetVelocity(const Vector2& velocity);

	/// Indicates whether the actor is currently using a thruster
	bool IsThrusterInUse() const;

protected:
	CActor&	m_Actor;
	Vector2 m_Velocity = Vector2(0.0f, 0.0f);
	bool	m_IsThrusting = false;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

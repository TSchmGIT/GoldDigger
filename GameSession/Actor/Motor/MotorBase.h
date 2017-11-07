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
	CMotorBase(CActor* actor);
	virtual ~CMotorBase();

	virtual void Tick();
	const Vector2& GetVelocity() const;
	void SetVelocity(const Vector2& velocity);

protected:
	CActor*	m_Actor = nullptr;
	Vector2 m_Velocity = Vector2(0.0f, 0.0f);
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

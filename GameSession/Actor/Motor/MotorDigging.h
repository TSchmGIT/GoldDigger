#pragma once
#include "GameSession/Actor/Motor/MotorBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CMotorDigging : public CMotorBase
{

public:
	CMotorDigging(const CMotorBase& other);
	CMotorDigging(const CMotorDigging& other) = default;
	virtual ~CMotorDigging() = default;

	const WorldPos& GetTargetPosition() const;
	void SetTargetPosition(const WorldPos& worldPos);

	float GetDiggingPower() const;
	void SetDiggingPower(float diggingPower);

	virtual void Tick() override;

protected:
	void ProcessTileDigging();

protected:
	WorldPos	m_TargetPos = WorldPos(0.0f, 0.0f);
	float		m_DiggingPower = 0.0f;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

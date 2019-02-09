#pragma once

#include "GameSessionNew/Actor/Motor/MotorDefault.h"
#include "GameSessionNew/GameObjects/IGameObject.h"
#include "GameSessionNew/Physics/CollisionObject.h"
#include "GameSessionNew/Rendering/IRenderElement.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class CTile;
class CInventory;
class CActorHealth;
class CActorEconomy;
class CEquipment;

enum class Layer : int;
}


namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CActor
	: public IRenderElement
	, public IGameObject
	, public ICollisionObject
{
public:
	CActor();
	CActor(const CActor& other) = delete;
	CActor(CActor&& other) = default;
	virtual ~CActor() = default;

public: // IGameObject
	virtual void InitAfterCreation() override;
	virtual void Tick() override;

public: // IRenderElement
	virtual void Draw() const override;

protected: // ICollisionObject 
	virtual WorldPos GetAABBOrigin() const override;
	virtual WorldPos GetAABBHalfs() const override;
	virtual Layer GetLayer() const override;

public:
	WorldPos GetAABBOriginOffset() const;

	const WorldPos& GetPosition() const;
	void SetPosition(const WorldPos& position);

	const CInventory& GetInventory() const;
	CInventory& GetInventory();

	const CActorEconomy& GetEconomy() const;
	CActorEconomy& GetEconomy();

	const CActorHealth& GetHealth() const;
	CActorHealth& GetHealth();

	const CEquipment& GetEquipment() const;
	CEquipment& GetEquipment();

	void StartDigging(const CTile& tile);
	void StopDigging();

protected:
	void UpdateCamera(const Vector2& deltaMovement) const;
	void UpdateUI() const;

	void CheckActorReset();

protected:
	WorldPos					m_Position = WorldPos({ 0.0f, 0.0f });

	UniquePtr<CActorHealth>		m_Health;
	UniquePtr<CActorEconomy>	m_Economy;
	UniquePtr<CInventory>		m_Inventory;
	UniquePtr<CEquipment>		m_Equipment;
	UniquePtr<CMotorBase>		m_Motor;

};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

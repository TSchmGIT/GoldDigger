#pragma once

#include "GameSession/Actor/Motor/MotorDefault.h"
#include "GameSession/GameObjects/IGameObject.h"
#include "GameSession/Physics/CollisionObject.h"
#include "GameSession/Rendering/IRenderElement.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class CTile;
class CInventory;
class CActorEconomy;

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
	CActor(const CActor& other);
	CActor(CActor&& other);
	virtual ~CActor();

public: // IGameObject
	virtual void PrepareTick() override;
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


	void StartDigging(const CTile& tile);
	void StopDigging();

protected:
	void UpdateCamera(const Vector2& deltaMovement) const;
	void UpdateUI() const;

protected:
	WorldPos				m_Position = WorldPos({ 0.0f, 0.0f });

	UniquePtr<CActorEconomy>	m_Economy = std::make_unique<CActorEconomy>();
	UniquePtr<CInventory>		m_Inventory = std::make_unique<CInventory>();
	UniquePtr<CMotorBase>		m_Motor = std::make_unique<CMotorDefault>(this);

};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

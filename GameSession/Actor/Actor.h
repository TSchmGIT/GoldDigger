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

	WorldPos GetPosition() const;
	void SetPosition(const WorldPos& position);

	const CInventory* GetInventory() const;
	CInventory* GetInventory();


	void StartDigging(const CTile& tile);
	void StopDigging();

protected:
	void UpdateCamera(const Vector2& deltaMovement) const;

	bool PerformSingleSweep(const Vector2& pos, const Vector2& halfs, const Vector2& delta, Vector2& newPos, Vector2& newDelta) const;

protected:
	WorldPos	m_Position = Vector2(0.0f, 0.0f);

	UniquePtr<CInventory> m_Inventory = std::make_unique<CInventory>();
	UniquePtr<CMotorBase> m_Motor = std::make_unique<CMotorDefault>(this);

};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

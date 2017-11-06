#pragma once

#include "GameSession/GameObjects/IGameObject.h"
#include "GameSession/Rendering/IRenderElement.h"
#include "GameSession/Physics/CollisionObject.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class CInventory;
enum class Layer : int;
}


namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CActor
	: public IRenderElement
	, public IGameObject
	, protected ICollisionObject
{
public:
	CActor();
	CActor(const CActor& other);
	virtual ~CActor();

public: // IGameObject
	virtual void Tick() override;

public: // IRenderElement
	virtual void Draw() const override;

protected: // ICollisionObject 
	virtual WorldPos GetAABBOrigin() const override;
	virtual WorldPos GetAABBHalfs() const override;
	WorldPos GetAABBOriginOffset() const;
	virtual Layer GetLayer() const override;

public:
	WorldPos GetPosition() const;
	void SetPosition(const WorldPos& position);

	const CInventory* GetInventory() const;

protected:
	void ProcessMovement(Vector2& deltaMovement);
	void UpdateCamera(const Vector2& deltaMovement) const;

	bool PerformSingleSweep(const Vector2& pos, const Vector2& halfs, const Vector2& delta, Vector2& newPos, Vector2& newDelta) const;

protected:
	WorldPos	m_Position;

	UniquePtr<CInventory> m_Inventory = std::make_unique<CInventory>();
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

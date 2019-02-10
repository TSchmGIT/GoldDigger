#pragma once

#include "GameSession\Manager\SingletonBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvmath
{
class AABB;
struct Sweep;
}

namespace hvgs
{
class ICollisionObject;
enum class Layer : int;
}

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CPhysicsManager : public CSingletonBase<CPhysicsManager>
{

public:
	CPhysicsManager();
	virtual ~CPhysicsManager();

public:
	void RegisterCollisionObject(const ICollisionObject* collisionObject);
	void UnregisterCollisionObject(const ICollisionObject* collisionObject);

public:
	const Vector2& GetGravity() const;

	bool SweepTest(const hvmath::AABB& object, const Vector2& delta, const Layer& layerMask, hvmath::Sweep& sweepResult, hvmath::AABB& collider) const;

protected:
	Vector<const ICollisionObject*> GetCollisionObjectsInRange(const WorldPos& worldPos, const Vector2& range) const;

protected:
	Set<const ICollisionObject*> m_ColliderSet;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

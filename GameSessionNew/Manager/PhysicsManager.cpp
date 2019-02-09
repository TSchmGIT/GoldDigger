#include "stdafx.h"
#include "PhysicsManager.h"

#include <hvmath\Physics\AABB.h>

#include "GameSessionNew/Physics/CollisionObject.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CPhysicsManager::CPhysicsManager()
{

}

//////////////////////////////////////////////////////////////////////////

CPhysicsManager::~CPhysicsManager()
{

}

//////////////////////////////////////////////////////////////////////////

Vector<const ICollisionObject*> CPhysicsManager::GetCollisionObjectsInRange(const WorldPos& worldPos, const Vector2& range) const
{
	Vector<const ICollisionObject*> result;

	Vector2 adjustedRange = hvmath::Abs(range);
	adjustedRange.x = hvmath::Max({ adjustedRange.x, 1.0f });
	adjustedRange.y = hvmath::Max({ adjustedRange.y, 1.0f });

	hvmath::AABB testBox(worldPos - adjustedRange * 0.5f, adjustedRange);
	hvmath::Hit dummy;

	for (auto&& collisionObject : m_ColliderSet)
	{
		// The aabb is not inside the range
		if (!testBox.IntersectAABB(collisionObject->GetAABB(), dummy))
		{
			continue;
		}

		result.emplace_back(collisionObject);
	}

	return result;
}

//////////////////////////////////////////////////////////////////////////

void CPhysicsManager::RegisterCollisionObject(const ICollisionObject* collisionObject)
{
	ASSERT_OR_EXECUTE(collisionObject, return);

#if _DEBUG
	//auto it = std::find_if(m_ColliderSet.begin(), m_ColliderSet.end(), [collisionObject](const ICollisionObject* element) { return element == collisionObject; });
	auto it = m_ColliderSet.find(collisionObject);
	ASSERT_OR_EXECUTE(it == m_ColliderSet.end(), return);
#endif

	m_ColliderSet.emplace(collisionObject);
}

//////////////////////////////////////////////////////////////////////////

void CPhysicsManager::UnregisterCollisionObject(const ICollisionObject* collisionObject)
{
	ASSERT_OR_EXECUTE(collisionObject, return);

	//auto it = std::find_if(m_ColliderSet.begin(), m_ColliderSet.end(), [collisionObject](const ICollisionObject* element) { return element == collisionObject; });
	auto it = m_ColliderSet.find(collisionObject);
	ASSERT_OR_EXECUTE(it != m_ColliderSet.end(), return);

	m_ColliderSet.erase(it);
}

//////////////////////////////////////////////////////////////////////////

const hvgs::Vector2& CPhysicsManager::GetGravity() const
{
	static const Vector2 gravity(0.0f, -9.81f * 0.75f);
	return gravity;
}

//////////////////////////////////////////////////////////////////////////

bool CPhysicsManager::SweepTest(const hvmath::AABB& object, const Vector2& delta, const Layer& layerMask, hvmath::Sweep& sweepResult, hvmath::AABB& collider) const
{
	Vector<hvmath::AABB> AABBList;
	AABBList.reserve(m_ColliderSet.size() - 1);

	for (auto&& collisionObject : GetCollisionObjectsInRange(object.pos, delta))
	{
		if (!collisionObject->IsEnabled())
		{
			continue;
		}
		
		if ((int(collisionObject->GetLayer()) & int(layerMask)) == 0)
		{
			continue;
		}

		AABBList.push_back(collisionObject->GetAABB());
	}

	return object.SweepInto(AABBList, delta, sweepResult, collider);
}

//////////////////////////////////////////////////////////////////////////

} // hvgs

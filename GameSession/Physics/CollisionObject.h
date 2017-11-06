#pragma once

#include <hvmath\Physics\AABB.h>

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
enum class Layer : int;
}

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class ICollisionObject
{

public:
	ICollisionObject();
	ICollisionObject(const ICollisionObject& other);
	ICollisionObject(ICollisionObject&& other);

	ICollisionObject& operator=(const ICollisionObject& other);
	ICollisionObject& operator=(ICollisionObject&& other);
	virtual ~ICollisionObject();

public:
	virtual Layer GetLayer() const = 0;
	virtual bool IsEnabled() const;
	const hvmath::AABB& GetAABB() const;

protected:
	virtual WorldPos GetAABBOrigin() const = 0;
	virtual WorldPos GetAABBHalfs() const = 0;

protected:
	hvmath::AABB	m_AABB;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

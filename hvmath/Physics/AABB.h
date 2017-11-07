#pragma once

#include "hvmath/Vector2/Vector2.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvmath
{

/////////////////////////////////////////////////////////////////////////////

struct Hit
{
	hvmath::Vector2<float> pos = { 0.0f, 0.0f };
	hvmath::Vector2<float> delta = { 0.0f, 0.0f };
	hvmath::Vector2<float> normal = { 0.0f, 0.0f };
	float time = 1.0f;
};

struct Sweep
{
	Hit hit;
	hvmath::Vector2<float> pos = { 0.0f, 0.0f };
	float time = 1.0f;
};

class AABB
{
public:
	AABB() = default;
	AABB(const hvmath::Vector2<float>& pos, const hvmath::Vector2<float>& half) : pos(pos), half(half) {};
	~AABB() = default;

	bool IntersectPoint(const hvmath::Vector2<float>& p_point, Hit& p_hit) const;
	bool IntersectSegment(const hvmath::Vector2<float>& point, const hvmath::Vector2<float>& delta, Hit& hit, float paddingX = 0.0f, float paddingY = 0.0f) const;
	bool IntersectAABB(const AABB& box, Hit& hit) const;
	bool SweepAABB(const AABB& p_box, const hvmath::Vector2<float>& p_delta, Sweep& p_sweep) const;
	bool SweepInto(const std::vector<AABB>& staticColliderList, const hvmath::Vector2<float>& delta, Sweep& sweep, AABB& collider) const;

public:
	hvmath::Vector2<float> pos;
	hvmath::Vector2<float> half;
};
/////////////////////////////////////////////////////////////////////////////

} // hvmath

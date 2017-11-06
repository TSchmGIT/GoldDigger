#include "stdafx.h"
#include "AABB.h"

#include "hvmath/Generic/Generic.inl"

//////////////////////////////////////////////////////////////////////////

namespace hvmath
{

const float EPSILON = 0.01f;

//////////////////////////////////////////////////////////////////////////

bool AABB::IntersectPoint(const Vector2<float>& point, Hit& hit) const
{
	float _deltaX = point.x - pos.x;
	float _pX = half.x - std::abs(_deltaX);

	if (_pX <= 0.0f)
		return false;

	float _deltaY = point.y - pos.y;
	float _pY = half.y - std::abs(_deltaY);

	if (_pY <= 0.0f)
		return false;

	if (_pX < _pY)
	{
		float _signX = Sign(_deltaX);
		hit.delta = Vector2<float>(_pX * _signX, 0.0f);
		hit.normal = Vector2<float>(_signX, 0.0f);
		hit.pos = Vector2<float>(pos.x + half.x * _signX, point.y);
	}
	else
	{
		float _signY = Sign(_deltaY);
		hit.delta = Vector2<float>(0.0f, _pY * _signY);
		hit.normal = Vector2<float>(0.0f, _signY);
		hit.pos = Vector2<float>(point.x, pos.y + half.y * _signY);
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////

bool AABB::IntersectSegment(const Vector2<float>& point, const Vector2<float>& delta, Hit& hit, float paddingX /*= 0.0f*/, float paddingY /*= 0.0f*/) const
{
	float _scaleX = 1.0f / delta.x;
	float _scaleY = 1.0f / delta.y;

	float _signX = Sign(_scaleX);
	float _signY = Sign(_scaleY);

	float _nearTimeX = (pos.x - _signX * (half.x + paddingX) - point.x) * _scaleX;
	float _nearTimeY = (pos.y - _signY * (half.y + paddingY) - point.y) * _scaleY;
	float _farTimeX = (pos.x + _signX * (half.x + paddingX) - point.x) * _scaleX;
	float _farTimeY = (pos.y + _signY * (half.y + paddingY) - point.y) * _scaleY;

	if (_nearTimeX > _farTimeY || _nearTimeY > _farTimeX)
		return false;

	float _nearTime = Max({ _nearTimeX, _nearTimeY });
	float _farTime = Min({ _farTimeX, _farTimeY });

	if (_nearTime >= 1.0f || _farTime <= 0.0f)
		return false;

	hit.time = Clamp(_nearTime, 0.0f, 1.0f);
	if (_nearTimeX > _nearTimeY)
		hit.normal = Vector2<float>(-_signX, 0.0f);
	else
		hit.normal = Vector2<float>(0.0f, -_signY);

	hit.delta = delta * hit.time;
	hit.pos = point + hit.delta;
	return true;
}

//////////////////////////////////////////////////////////////////////////

bool AABB::IntersectAABB(const AABB& box, Hit& hit) const
{
	float _deltaX = box.pos.x - pos.x;
	float _pX = (box.half.x + half.x) - std::abs(_deltaX);
	if (_pX < 0.0f)
		return false;

	float _deltaY = box.pos.y - pos.y;
	float _pY = (box.half.y + half.y) - std::abs(_deltaY);
	if (_pY < 0.0f)
		return false;

	if (_pX < _pY)
	{
		float _signX = Sign(_deltaX);
		hit.delta = { _pX * _signX, 0.0f };
		hit.normal = { _signX, 0.0f };
		hit.pos = { pos.x + half.x * _signX, box.pos.y };
	}
	else
	{
		float _signY = Sign(_deltaY);
		hit.delta = { 0.0f, _pY * _signY };
		hit.normal = { 0.0f, _signY };
		hit.pos = { box.pos.x, pos.y + half.y * _signY };
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////

bool AABB::SweepAABB(const AABB& box, const Vector2<float>& delta, Sweep& sweep) const
{
	if (delta.x == 0.0f && delta.y == 0.0f)
	{
		sweep.pos = box.pos;
		if (IntersectAABB(box, sweep.hit))
		{
			sweep.time = sweep.hit.time = 0.0f;
			return true;
		}
		else
		{
			sweep.time = 1.0f;
			return false;
		}
	}
	else
	{
		if (IntersectSegment(box.pos, delta, sweep.hit, box.half.x, box.half.y))
		{
			sweep.time = Clamp(sweep.hit.time, 0.0f, 1.0f);
			sweep.pos = box.pos + delta * sweep.time + sweep.hit.normal * EPSILON;
			Vector2<float> _dir = Vector2<float>::Normalize(delta);
			sweep.hit.pos.x += _dir.x * box.half.x;
			sweep.hit.pos.y += _dir.y * box.half.y;

			return true;
		}
		else
		{
			sweep.pos = box.pos + delta;
			sweep.time = 1.0f;

			return false;
		}
	}
}

//////////////////////////////////////////////////////////////////////////

bool AABB::SweepInto(const std::vector<AABB>& staticColliderList, const hvmath::Vector2<float>& delta, Sweep& sweep, AABB& collider) const
{
	sweep.time = 1.0f;
	sweep.pos = pos + delta;

	Sweep _tmpSweep;
	bool _result = false;

	for (const AABB& aabb : staticColliderList)
	{
		_result |= aabb.SweepAABB(*this, delta, _tmpSweep);

		if (_tmpSweep.time < sweep.time)
		{
			sweep.hit = _tmpSweep.hit;
			sweep.pos = _tmpSweep.pos;
			sweep.time = _tmpSweep.time;
			collider = aabb;
		}
	}

	return _result;
}

//////////////////////////////////////////////////////////////////////////

} // hvmath

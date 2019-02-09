#include "stdafx.h"
#include "DebugRender.h"

#include <hvmath\Physics\AABB.h>

#include "GameSessionNew/Manager/CameraManager.h"
#include "GameSessionNew/Camera/Camera.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

void DebugRender::DrawLine(sf::RenderWindow* window, const ScreenPos& start, const ScreenPos& end)
{
	// Test if rendering is needed
	hvmath::AABB onScreenTest{ start + (end - start) * 0.5f, (end - start) * 0.5f };
	hvmath::AABB renderAABB{ { 0.0f, 0.0f }, window->getSize() };

	hvmath::Hit dummyHit;
	if (!renderAABB.IntersectAABB(onScreenTest, dummyHit))
	{
		return;
	}

	// Create two vertices and draw them
	sf::Vertex vertices[]{ start, end };
	window->draw(vertices, 2, sf::PrimitiveType::Lines);
}

//////////////////////////////////////////////////////////////////////////

void DebugRender::DrawRect(sf::RenderWindow* window, const hvmath::AABB& worldBounds)
{
	auto&& cam = CCameraManager::Get().GetActive();
	ASSERT_OR_EXECUTE(cam, return);

	hvmath::AABB screenBounds;
	screenBounds.pos = cam->WorldToScreenPoint(worldBounds.pos);
	screenBounds.half = cam->WorldToScreenDirection(worldBounds.half);

	// Test if rendering is needed
	hvmath::AABB renderAABB{ { 0.0f, 0.0f }, window->getSize() };
	hvmath::Hit dummyHit;
	if (!renderAABB.IntersectAABB(screenBounds, dummyHit))
	{
		return;
	}

	sf::Vertex vertices[]{
		screenBounds.pos - screenBounds.half,
		screenBounds.pos + ScreenPos{screenBounds.half.x, -screenBounds.half.y},
		screenBounds.pos + screenBounds.half,
		screenBounds.pos + ScreenPos{-screenBounds.half.x, screenBounds.half.y},
		screenBounds.pos - screenBounds.half };
	window->draw(vertices, 5, sf::LineStrip);
}

//////////////////////////////////////////////////////////////////////////

} // hvgs

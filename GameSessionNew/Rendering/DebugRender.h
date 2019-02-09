#pragma once

/////////////////////////////////////////////////////////////////////////////

namespace hvmath
{
class AABB;
}

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

/// Provides methods that can be used to debug rendering issues
class DebugRender
{

private:
	DebugRender() = default;

public:
	static void DrawLine(sf::RenderWindow* window, const ScreenPos& start, const ScreenPos& end);
	static void DrawRect(sf::RenderWindow* window, const hvmath::AABB& renderBounds);
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

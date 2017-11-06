#include "stdafx.h"
#include "Camera.h"

#include "GameSession/Manager/InputManager.h"
#include "GameSession/Manager/RenderManager.h"
#include "GameSession/Manager/TimeManager.h"
#include "Rendering/DebugRender.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

const float ZOOM_LEVEL_MAX = 2.0f;
const float ZOOM_LEVEL_MIN = 0.5f;

//////////////////////////////////////////////////////////////////////////

CCamera::CCamera()
	: m_Position(0.0f, 0.0f)
	, m_ZoomFactor(1.0f)
{

}

//////////////////////////////////////////////////////////////////////////

CCamera::~CCamera()
{

}

//////////////////////////////////////////////////////////////////////////

void CCamera::Tick()
{
	UpdateZoom();
}

//////////////////////////////////////////////////////////////////////////

ScreenPos CCamera::WorldToScreenPoint(const WorldPos& worldPos) const
{
	WorldPos worldDelta(worldPos - m_Position);
	ScreenPos screenDelta(worldDelta * BASE_TILE_SIZE_PX);

	// #TODO Apply zoom
	screenDelta *= m_ZoomFactor;

	screenDelta += Vector2{ CRenderManager::Get().GetScreenWidth() * 0.5f, CRenderManager::Get().GetScreenHeight() * 0.5f };

	screenDelta.y = CRenderManager::Get().GetScreenHeight() - screenDelta.y;

	return screenDelta;
}

//////////////////////////////////////////////////////////////////////////

hvgs::ScreenPos CCamera::WorldToScreenDirection(const WorldPos& worldDir) const
{
	return worldDir * BASE_TILE_SIZE_PX * m_ZoomFactor;
}

//////////////////////////////////////////////////////////////////////////

WorldPos CCamera::ScreenToWorldPoint(const ScreenPos& screenPos) const
{
	ScreenPos screenPosNew{ screenPos.x, CRenderManager::Get().GetScreenHeight() - screenPos.y };

	float pixelPerTile = BASE_TILE_SIZE_PX * m_ZoomFactor;
	WorldPos screenToWorldPos = screenPosNew / pixelPerTile;

	float tilesOnScreenX = hvmath::Ceil<float, float>(CRenderManager::Get().GetScreenWidth() / pixelPerTile);
	float tilesOnScreenY = hvmath::Ceil<float, float>(CRenderManager::Get().GetScreenHeight() / pixelPerTile);
	Vector2 worldOffset{ m_Position.x - tilesOnScreenX * 0.5f, m_Position.y - tilesOnScreenY * 0.5f };

	return worldOffset + screenToWorldPos;
}

//////////////////////////////////////////////////////////////////////////

bool CCamera::IsInView(const sf::FloatRect& worldRect) const
{
	float pixelPerTile = BASE_TILE_SIZE_PX * m_ZoomFactor;
	float tilesOnScreenX = hvmath::Ceil<float, float>(CRenderManager::Get().GetScreenWidth() / pixelPerTile);
	float tilesOnScreenY = hvmath::Ceil<float, float>(CRenderManager::Get().GetScreenHeight() / pixelPerTile);

	sf::FloatRect rect(
		m_Position.x - tilesOnScreenX * 0.5f, // left
		m_Position.y - tilesOnScreenY * 0.5f, // top
		tilesOnScreenX,
		tilesOnScreenY);

	return rect.intersects(worldRect);
}

//////////////////////////////////////////////////////////////////////////

const Vector2& CCamera::GetPosition() const
{
	return m_Position;
}

//////////////////////////////////////////////////////////////////////////

void CCamera::SetPosition(const Vector2& position)
{
	if (m_Position == position)
	{
		return;
	}

	m_Position = position;
}

//////////////////////////////////////////////////////////////////////////

void CCamera::SetPosition(Vector2&& position)
{
	if (m_Position == position)
	{
		return;
	}

	m_Position = position;
}

//////////////////////////////////////////////////////////////////////////

float CCamera::GetZoomFactor() const
{
	return m_ZoomFactor;
}

//////////////////////////////////////////////////////////////////////////

void CCamera::SetZoomFactor(float zoomFactor)
{
	m_ZoomFactor = zoomFactor;
}

//////////////////////////////////////////////////////////////////////////

void CCamera::UpdateZoom()
{
	// Zoom reset
	if (CInputManager::Get().IsMouseButtonDown(MouseButton::Middle))
	{
		m_ZoomFactor = 1.0f;
		return;
	}

	float scrollWheelDelta = CInputManager::Get().GetMouseWheelDelta();
	if (scrollWheelDelta == 0)
	{
		return;
	}

	if (scrollWheelDelta < 0)
	{
		m_ZoomFactor *= 0.9f;
	}
	else if (scrollWheelDelta > 0)
	{
		m_ZoomFactor /= 0.9f;
	}

	m_ZoomFactor = hvmath::Clamp(m_ZoomFactor, ZOOM_LEVEL_MIN, ZOOM_LEVEL_MAX);

}

//////////////////////////////////////////////////////////////////////////

void CCamera::DrawDebug()
{
	//// Draw tile grid lines
	//float screenWidth = float(CRenderManager::Get().GetScreenWidth());
	//float screenHeight = float(CRenderManager::Get().GetScreenHeight());

	//const int linesHor = int(hvmath::Ceil(screenWidth / (BASE_TILE_SIZE_PX * m_ZoomFactor)));
	//const int linesVer = int(hvmath::Ceil(screenHeight / (BASE_TILE_SIZE_PX * m_ZoomFactor)));

	//for (float x = 0; x < screenWidth; x += screenWidth / linesHor)
	//{
	//	DebugRender::DrawLine(CRenderManager::GetMutable().GetWindow(), { x, 0.0f }, { x, screenHeight });
	//}

	//for (float y = 0; y < screenHeight; y += screenHeight / linesVer)
	//{
	//	DebugRender::DrawLine(CRenderManager::GetMutable().GetWindow(), { 0.0f, y }, { screenWidth, y });
	//}
}

//////////////////////////////////////////////////////////////////////////

} // hvgs

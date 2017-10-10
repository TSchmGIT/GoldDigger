#include "stdafx.h"
#include "Actor.h"

#include "GameSession/Manager/RenderManager.h"
#include "GameSession/Rendering/Textures/EnumsTexture.h"
#include "GameSession/Manager/TimeManager.h"
#include "GameSession/Manager/InputManager.h"
#include "Manager/CameraManager.h"
#include "Camera/Camera.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

////////////////////////////////////////////////////////////////////////////

CActor::CActor()
	: m_Position()
{
}

//////////////////////////////////////////////////////////////////////////

CActor::~CActor()
{

}

//////////////////////////////////////////////////////////////////////////

void CActor::Tick()
{
	// Get Input
	float hor = CInputManager::Get().GetAxis(Axis::Horizontal);
	float ver = CInputManager::Get().GetAxis(Axis::Vertical);

	// Calculate delta movement
	Vector2 deltaMovement = Vector2(hor, ver) * 500.0f * CTimeManager::Get().GetGameDeltaTime();

	m_Position += deltaMovement;

	CCamera* cam = CCameraManager::GetMutable().GetActive();
	ASSERT_OR_EXECUTE(cam, return);
	ScreenPos screenPos = cam->WorldToScreenPoint(m_Position);

	//float deltaXMax = screenPos.x + 100.0f - CRenderManager::Get().GetScreenWidth();
	//if (deltaXMax > 0)
	//{
	//	cam->SetPosition(cam->GetPosition() + ScreenPos(deltaXMax, 0.0f));
	//}
	//float deltaXMin = screenPos.x - 100.0f;
	//if (deltaXMin < 0)
	//{
	//	cam->SetPosition(cam->GetPosition() + ScreenPos(deltaXMin, 0.0f));
	//}
	//float deltaYMax = screenPos.y - 100.0f;
	//if (deltaYMax < 0)
	//{
	//	cam->SetPosition(cam->GetPosition() + ScreenPos(0.0f, -deltaYMax));
	//}
	//float deltaYMin = screenPos.y + 100.0f - CRenderManager::Get().GetScreenHeight();
	//if (deltaYMin > 0)
	//{
	//	cam->SetPosition(cam->GetPosition() + ScreenPos(0.0f, -deltaYMin));
	//}

}

//////////////////////////////////////////////////////////////////////////

void CActor::Draw() const
{
	CRenderManager::GetMutable().DrawSpriteWorld(m_Position, TextureName::Actor);

	// Debug
	std::ostringstream ss;
	ss << "(" << m_Position.x << ", " << m_Position.y << ")";
	CRenderManager::GetMutable().DrawTextWorld(m_Position, ss.str(), FontName::Courier_New, 12);
}

//////////////////////////////////////////////////////////////////////////

Vector2 CActor::GetPosition() const
{
	return m_Position;
}

//////////////////////////////////////////////////////////////////////////

void CActor::SetPosition(const Vector2& position)
{
	if (m_Position == position)
	{
		return;
	}

	m_Position = position;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs

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
	float hor = CInputManager::Get().GetAxis(Axis::Horizontal);

	Vector2 deltaMovement(hor * 500.0f * CTimeManager::Get().GetGameDeltaTime(), 0.0f);

	m_Position += deltaMovement;

	CCamera* cam = CCameraManager::GetMutable().GetActive();
	ASSERT_OR_EXECUTE(cam, return);
	Vector2 screenPos = cam->WorldToScreenPoint(m_Position);

	float deltaXMax = screenPos.x + 100.0f - CRenderManager::Get().GetScreenWidth();
	if (deltaXMax > 0)
	{
		cam->SetPosition(cam->GetPosition() + Vector2(deltaXMax, 0.0f));
	}
	float deltaXMin = screenPos.x - 100.0f;
	if (deltaXMin < 0)
	{
		cam->SetPosition(cam->GetPosition() + Vector2(deltaXMin, 0.0f));
	}
}

//////////////////////////////////////////////////////////////////////////

void CActor::Draw() const
{
	CRenderManager::GetMutable().DrawSpriteWorld(m_Position, TextureName::Actor);
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

#include "stdafx.h"
#include "UIButton.h"
#include "..\Manager\RenderManager.h"
#include "..\Rendering\Textures\EnumsTexture.h"
#include "..\..\hvmath\Physics\AABB.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

//////////////////////////////////////////////////////////////////////////

CUIButton::CUIButton()
{

}

//////////////////////////////////////////////////////////////////////////

CUIButton::~CUIButton()
{

}

//////////////////////////////////////////////////////////////////////////

void CUIButton::Draw() const
{
	CRenderManager::GetMutable().DrawSprite(m_Position, GetTextureName());
}

//////////////////////////////////////////////////////////////////////////

const hvgs::ScreenPos& CUIButton::GetSize() const
{
	return m_Size;
}

//////////////////////////////////////////////////////////////////////////

void CUIButton::SetSize(const ScreenPos& size)
{
	m_Size = size;
}

//////////////////////////////////////////////////////////////////////////

const hvgs::ScreenPos& CUIButton::GetPosition() const
{
	return m_Position;
}

//////////////////////////////////////////////////////////////////////////

void CUIButton::SetPosition(const ScreenPos& position)
{
	m_Position = position;
}

//////////////////////////////////////////////////////////////////////////

void CUIButton::OnMouseClicked(const ScreenPos& pos)
{
	IUIEventHandler::OnMouseClicked(pos);
}

//////////////////////////////////////////////////////////////////////////

void CUIButton::OnMouseMove(const ScreenPos&, const ScreenPos& pos)
{
	hvmath::AABB aabb(m_Position, m_Size * 0.5f);

	hvmath::Hit hit;
	bool isOverButton = aabb.IntersectPoint(pos, hit);

	if (isOverButton)
	{
		m_State = ButtonState::Hover;
	}
	else
	{
		m_State = ButtonState::Default;
	}
}

//////////////////////////////////////////////////////////////////////////

hvgs::TextureName CUIButton::GetTextureName() const
{
	switch (m_State)
	{
	default: /* fallthrough */
	case hvgs::ui::ButtonState::Default:
		return TextureName::Button_Default;
	case hvgs::ui::ButtonState::Hover:
		return TextureName::Button_Hover;
	case hvgs::ui::ButtonState::Pressed:
		return TextureName::Button_Pressed;
	case hvgs::ui::ButtonState::Deactivated:
		return TextureName::Button_Deactivated;
	}
}

//////////////////////////////////////////////////////////////////////////

} // hvgs::ui

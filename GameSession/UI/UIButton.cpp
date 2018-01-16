#include "stdafx.h"
#include "UIButton.h"
#include "..\Manager\RenderManager.h"
#include "..\Rendering\Textures\EnumsTexture.h"
#include "..\..\hvmath\Physics\AABB.h"
#include "Manager\InputManager.h"

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
	CRenderManager::GetMutable().DrawSprite(m_Position, GetTextureName(), m_Size, Alignment::TopLeft);
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

	// execute action
	if (!IsOverButton(pos))
	{
		return;
	}

	if (m_Action)
	{
		m_Action();
	}
}

//////////////////////////////////////////////////////////////////////////

void CUIButton::OnMouseMove(const ScreenPos&, const ScreenPos& pos)
{
	if (IsOverButton(pos))
	{
		m_State = m_IsPressed ? ButtonState::Pressed : ButtonState::Hover;
	}
	else
	{
		m_State = ButtonState::Default;
	}
}

//////////////////////////////////////////////////////////////////////////

void CUIButton::OnMouseDown(const ScreenPos& pos)
{
	if (IsOverButton(pos))
	{
		m_IsPressed = true;
		m_State = ButtonState::Pressed;
	}
}

//////////////////////////////////////////////////////////////////////////

void CUIButton::OnMouseUp(const ScreenPos& pos)
{
	m_IsPressed = false;
	m_State = IsOverButton(pos) ? ButtonState::Hover : ButtonState::Default;
}

//////////////////////////////////////////////////////////////////////////

hvgs::TextureName CUIButton::GetTextureName() const
{
	auto it = m_ButtonTextures.find(m_State);
	ASSERT_OR_EXECUTE(it != m_ButtonTextures.end(), return TextureName::INVALID);

	return it->second;
}

//////////////////////////////////////////////////////////////////////////

bool CUIButton::IsOverButton(const ScreenPos& pos) const
{
	hvmath::AABB aabb(m_Position + m_Size * 0.5f, m_Size * 0.5f);

	static hvmath::Hit hit;
	return aabb.IntersectPoint(pos, hit);

}

//////////////////////////////////////////////////////////////////////////

void CUIButton::SetAction(std::function<void()> action)
{
	m_Action = action;
}

//////////////////////////////////////////////////////////////////////////

hvgs::TextureName CUIButton::GetTextureForState(ButtonState state) const
{
	auto it = m_ButtonTextures.find(state);
	ASSERT_OR_EXECUTE(it != m_ButtonTextures.end(), return TextureName::INVALID);

	return it->second;
}

//////////////////////////////////////////////////////////////////////////

void CUIButton::SetTextureForState(ButtonState state, TextureName textureName)
{
	auto it = m_ButtonTextures.find(state);
	ASSERT_OR_EXECUTE(it != m_ButtonTextures.end(), return);

	it->second = textureName;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs::ui

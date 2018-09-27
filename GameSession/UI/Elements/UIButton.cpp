#include "stdafx.h"
#include "UIButton.h"

#include <hvmath/Physics/AABB.h>

#include "GameSession/Manager/InputManager.h"
#include "GameSession/Manager/RenderManager.h"
#include "GameSession/Rendering/Textures/EnumsTexture.h"
#include "GameSession/UI/Scenes/BaseScene.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

//////////////////////////////////////////////////////////////////////////

CUIButton::CUIButton(const CBaseScene& baseScene)
	: IUIEventHandler()
	, m_BaseScene(baseScene)
{
}

//////////////////////////////////////////////////////////////////////////

CUIButton::CUIButton(const CUIButton& other)
	:IUIEventHandler(other)
	, m_BaseScene(other.m_BaseScene)
{
}

//////////////////////////////////////////////////////////////////////////

void CUIButton::Draw() const
{
	CRenderManager::GetMutable().DrawSpriteUI(GetPosition(), GetTextureName(), m_Size, Alignment::TopLeft);

	CRenderManager::GetMutable().DrawText(GetPosition() + GetSize() * 0.5f, m_TextInfo.Text, m_TextInfo.TextAlignment, m_TextInfo.TextFont, m_TextInfo.TextSize, m_TextInfo.TextColor);
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

	if (!m_BaseScene.IsShown())
	{
		return;
	}

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

void CUIButton::OnMouseMove(const ScreenPos& delta, const ScreenPos& pos)
{
	IUIEventHandler::OnMouseMove(delta, pos);

	if (!m_BaseScene.IsShown())
	{
		return;
	}

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
	IUIEventHandler::OnMouseDown(pos);

	if (!m_BaseScene.IsShown())
	{
		return;
	}

	if (IsOverButton(pos))
	{
		m_IsPressed = true;
		m_State = ButtonState::Pressed;
	}
}

//////////////////////////////////////////////////////////////////////////

void CUIButton::OnMouseUp(const ScreenPos& pos)
{
	IUIEventHandler::OnMouseUp(pos);

	if (!m_BaseScene.IsShown())
	{
		return;
	}

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
	hvmath::AABB aabb(m_Position + m_BaseScene.GetPivotPoint() + m_Size * 0.5f, m_Size * 0.5f);

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

const hvgs::String& CUIButton::GetText() const
{
	return m_TextInfo.Text;
}

//////////////////////////////////////////////////////////////////////////

void CUIButton::SetText(const String& text)
{
	m_TextInfo.Text = text;
}

//////////////////////////////////////////////////////////////////////////

hvgs::Alignment CUIButton::GetTextAlignment() const
{
	return m_TextInfo.TextAlignment;
}

//////////////////////////////////////////////////////////////////////////

void CUIButton::SetTextAlignment(Alignment alignment)
{
	m_TextInfo.TextAlignment = alignment;
}

//////////////////////////////////////////////////////////////////////////

hvgs::FontName CUIButton::GetTextFont() const
{
	return m_TextInfo.TextFont;
}

//////////////////////////////////////////////////////////////////////////

void CUIButton::SetTextFont(FontName fontName)
{
	m_TextInfo.TextFont = fontName;
}

//////////////////////////////////////////////////////////////////////////

hvgs::FontSize CUIButton::GetTextSize() const
{
	return m_TextInfo.TextSize;
}

//////////////////////////////////////////////////////////////////////////

void CUIButton::SetTextSize(FontSize fontSize)
{
	m_TextInfo.TextSize = fontSize;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs::ui

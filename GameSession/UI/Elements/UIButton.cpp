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

void CUIButton::Draw() const
{
	CRenderManager::GetMutable().DrawSpriteUI(GetPosition(), GetTextureName(), GetSize(), GetAlignment());

	auto textPos = GetPosition();
	CRenderManager::AdjustPivot(textPos, GetSize(), GetAlignment());

	CRenderManager::GetMutable().DrawTextUI(textPos + GetSize() * 0.5f, m_TextInfo.Text, m_TextInfo.TextAlignment, m_TextInfo.TextFont, m_TextInfo.TextSize, m_TextInfo.TextColor);

	// Draw selection overlay when hovered or pressed OR when pressed (design decision)
	if (ButtonState state = m_State;
		GetIsSelected() || state == ButtonState::Hover || state == ButtonState::Pressed)
	{
		// When a selected button should always just display its default selected overlay
		if (state == ButtonState::Hover && GetIsSelected())
		{
			state = ButtonState::Default;
		}

		if (TextureName overlayTexture = GetSelectionOverlayTexture(state);
			overlayTexture != TextureName::INVALID)
		{
			CRenderManager::GetMutable().DrawSpriteUI(GetPosition(), overlayTexture, GetSize(), GetAlignment());
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void CUIButton::OnMouseClicked(const ScreenPos& pos)
{
	IUIEventHandler::OnMouseClicked(pos);

	if (!m_BaseScene.IsShown())
	{
		return;
	}

	if (GetIsDisabled())
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

	if (GetIsDisabled())
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

	if (GetIsDisabled())
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

	if (GetIsDisabled())
	{
		return;
	}

	m_IsPressed = false;
	m_State = IsOverButton(pos) ? ButtonState::Hover : ButtonState::Default;
}

//////////////////////////////////////////////////////////////////////////

hvgs::TextureName CUIButton::GetTextureName() const
{
	return GetTextureForState(m_State);
}

//////////////////////////////////////////////////////////////////////////

bool CUIButton::IsOverButton(const ScreenPos& pos) const
{
	// Get local position and button size
	ScreenPos posOffset = GetPosition();
	Vector2 buttonSize = GetSize();

	// adjust position for alignment (local space)
	CRenderManager::AdjustPivot(posOffset, buttonSize, GetAlignment());

	// Calculate the final local position
	auto finalPos = posOffset + m_BaseScene.GetPivotPoint() + buttonSize * 0.5f;

	// Scale position and button size to global coords
	CRenderManager::Get().ScaleUIPos(finalPos);
	CRenderManager::Get().ScaleUISize(buttonSize);

	hvmath::AABB aabb(finalPos, buttonSize * 0.5f);

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
	if (GetIsSelected())
	{
		if (state == ButtonState::Default)
		{
			state = ButtonState::Pressed;
		}
	}

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

void CUIButton::SetTextureForAllStates(TextureName textureName)
{
	for (int i = 0; i < int(ButtonState::Count); ++i)
	{
		auto state = ButtonState(i);
		SetTextureForState(state, textureName);
	}
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

bool CUIButton::GetIsSelected() const
{
	return m_IsSelected;
}

//////////////////////////////////////////////////////////////////////////

void CUIButton::SetIsSelected(bool isSelected)
{
	m_IsSelected = isSelected;
}

//////////////////////////////////////////////////////////////////////////

int CUIButton::GetMetaData() const
{
	return m_MetaData;
}

//////////////////////////////////////////////////////////////////////////

void CUIButton::SetMetaData(int metaData)
{
	m_MetaData = metaData;
}

//////////////////////////////////////////////////////////////////////////

bool CUIButton::GetIsDisabled() const
{
	return m_IsDisabled;
}

//////////////////////////////////////////////////////////////////////////

void CUIButton::SetIsDisabled(bool isDisabled)
{
	if (m_IsDisabled == isDisabled)
	{
		return;
	}

	m_IsDisabled = isDisabled;
	m_State = isDisabled ? ButtonState::Deactivated : ButtonState::Default;
}

//////////////////////////////////////////////////////////////////////////

hvgs::Alignment CUIButton::GetAlignment() const
{
	return m_Alignment;
}

//////////////////////////////////////////////////////////////////////////

void CUIButton::SetAlignment(Alignment alignment)
{
	m_Alignment = alignment;
}

//////////////////////////////////////////////////////////////////////////

hvgs::TextureName CUIButton::GetSelectionOverlayTexture(ButtonState state) const
{
	auto itFind = m_SelectionOverlayTextures.find(state);
	if (itFind == m_SelectionOverlayTextures.end())
	{
		ASSERT_TEXT(false, "Tried to get selection overlay texture for invalid state");
		return TextureName::INVALID;
	}

	return itFind->second;
}

//////////////////////////////////////////////////////////////////////////

void CUIButton::SetSelectionOverlayTexture(ButtonState buttonState, TextureName texture)
{
	m_SelectionOverlayTextures[buttonState] = texture;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs::ui

#include "stdafx.h"
#include "UISpriteWithText.h"
#include "Manager/RenderManager.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

//////////////////////////////////////////////////////////////////////////

CUISpriteWithText::CUISpriteWithText(TextureName spriteTexture, const TextUIInfo& textInfo)
	: m_SpriteTexture(spriteTexture)
	, m_TextInfo(textInfo)
{
}

//////////////////////////////////////////////////////////////////////////

void CUISpriteWithText::Draw() const
{
	CRenderManager::GetMutable().DrawSpriteUI(GetPosition(), m_SpriteTexture, GetSize(), Alignment::TopLeft);
	CRenderManager::GetMutable().DrawText(GetPosition() + GetSize() * 0.5f, m_TextInfo.Text, m_TextInfo.TextAlignment, m_TextInfo.TextFont, m_TextInfo.TextSize, m_TextInfo.TextColor);
}

//////////////////////////////////////////////////////////////////////////

hvgs::TextureName CUISpriteWithText::GetSpriteTexture() const
{
	return m_SpriteTexture;
}

//////////////////////////////////////////////////////////////////////////

void CUISpriteWithText::SetSpriteTexture(TextureName spriteTexture)
{
	m_SpriteTexture = spriteTexture;
}

//////////////////////////////////////////////////////////////////////////

const hvgs::String& CUISpriteWithText::GetText() const
{
	return m_TextInfo.Text;
}

//////////////////////////////////////////////////////////////////////////

void CUISpriteWithText::SetText(const String& text)
{
	m_TextInfo.Text = text;
}

//////////////////////////////////////////////////////////////////////////

hvgs::Alignment CUISpriteWithText::GetTextAlignment() const
{
	return m_TextInfo.TextAlignment;
}

//////////////////////////////////////////////////////////////////////////

void CUISpriteWithText::SetTextAlignment(Alignment alignment)
{
	m_TextInfo.TextAlignment = alignment;
}

//////////////////////////////////////////////////////////////////////////

hvgs::FontName CUISpriteWithText::GetTextFont() const
{
	return m_TextInfo.TextFont;
}

//////////////////////////////////////////////////////////////////////////

void CUISpriteWithText::SetTextFont(FontName fontName)
{
	m_TextInfo.TextFont = fontName;
}

//////////////////////////////////////////////////////////////////////////

hvgs::FontSize CUISpriteWithText::GetTextSize() const
{
	return m_TextInfo.TextSize;
}

//////////////////////////////////////////////////////////////////////////

void CUISpriteWithText::SetTextSize(FontSize fontSize)
{
	m_TextInfo.TextSize = fontSize;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs::ui

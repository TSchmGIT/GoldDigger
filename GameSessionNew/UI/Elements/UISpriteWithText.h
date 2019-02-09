#pragma once
#include "UIButton.h"

#include "GameSessionNew/Rendering/Textures/EnumsTexture.h"
#include "UIWidget.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

/////////////////////////////////////////////////////////////////////////////

class CUISpriteWithText
	: public CUIWidget
{

public:
	CUISpriteWithText() = delete;
	CUISpriteWithText(TextureName spriteTexture, const TextUIInfo& textInfo);
	virtual ~CUISpriteWithText() = default;

public:
	void Draw() const;

public:
	TextureName GetSpriteTexture() const;
	void SetSpriteTexture(TextureName spriteTexture);

	const String& GetText() const;
	void SetText(const String& text);

	Alignment GetTextAlignment() const;
	void SetTextAlignment(Alignment alignment);

	FontName GetTextFont() const;
	void SetTextFont(FontName fontName);

	FontSize GetTextSize() const;
	void SetTextSize(FontSize fontSize);

protected:
	TextureName		m_SpriteTexture = TextureName::INVALID;		///< The texture that should be used for that sprite
	TextUIInfo		m_TextInfo;									///< Text info describing how the text should be displayed inside the sprite
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui

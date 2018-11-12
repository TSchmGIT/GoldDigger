#pragma once

#include "GameSession/UI/Elements/UIWidget.h"

#include "GameSession/Rendering/Fonts/EnumsFont.h"
#include "GameSession/Rendering/Textures/EnumsTexture.h"
#include "GameSession/Rendering/Textures/EnumsTexture.h"
#include "GameSession/UI/IUIEventHandler.h"
#include "GameSession/UI/UIStructs.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{
class CBaseScene;
}

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

/////////////////////////////////////////////////////////////////////////////

enum class ButtonState
{
	Default = 0,
	Hover,
	Pressed,
	Deactivated,
	Count
};

class CUIButton
	: public CUIWidget
	, public IUIEventHandler
{

public:
	CUIButton() = delete;
	CUIButton(const CBaseScene& baseScene);
	virtual ~CUIButton() = default;

	virtual void Draw() const;

public:
	TextureName GetTextureForState(ButtonState state) const;
	void SetTextureForState(ButtonState state, TextureName textureName);
	void SetTextureForAllStates(TextureName textureName);

	TextureName GetSelectionOverlayTexture(ButtonState state) const;
	void SetSelectionOverlayTexture(ButtonState buttonState, TextureName texture);

	bool GetIsSelected() const;
	void SetIsSelected(bool isSelected);

	bool GetIsDisabled() const;
	void SetIsDisabled(bool isDisabled);

	Alignment GetAlignment() const;
	void SetAlignment(Alignment alignment);

	int GetMetaData() const;
	void SetMetaData(int metaData);

	const String& GetText() const;
	void SetText(const String& text);

	Alignment GetTextAlignment() const;
	void SetTextAlignment(Alignment alignment);

	FontName GetTextFont() const;
	void SetTextFont(FontName fontName);

	FontSize GetTextSize() const;
	void SetTextSize(FontSize fontSize);

	void SetAction(std::function<void()> action);

protected:
	virtual void OnMouseClicked(const ScreenPos& pos) override;
	virtual void OnMouseMove(const ScreenPos& delta, const ScreenPos& pos) override;
	virtual void OnMouseDown(const ScreenPos& pos) override;
	virtual void OnMouseUp(const ScreenPos& pos) override;

	TextureName GetTextureName() const;

protected:
	bool IsOverButton(const ScreenPos& pos) const;

protected:
	const CBaseScene& m_BaseScene;

	TextUIInfo	m_TextInfo;

	Alignment	m_Alignment = Alignment::TopLeft;
	ButtonState m_State = ButtonState::Default;
	bool		m_IsDisabled = false;
	bool		m_IsPressed = false;
	bool		m_IsSelected = false;

	int			m_MetaData = 0;

	Map<ButtonState, TextureName>	m_SelectionOverlayTextures = { {ButtonState::Default, TextureName::INVALID},
																	{ButtonState::Hover, TextureName::INVALID},
																	{ButtonState::Pressed, TextureName::INVALID},
																	{ButtonState::Deactivated, TextureName::INVALID } };

	Map<ButtonState, TextureName>	m_ButtonTextures = { {ButtonState::Default, TextureName::BUTTON_DEFAULT},
															{ButtonState::Hover, TextureName::BUTTON_HOVER},
															{ButtonState::Pressed, TextureName::BUTTON_PRESSED },
															{ButtonState::Deactivated, TextureName::BUTTON_DEACTIVATED } };

	std::function<void()> m_Action;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui

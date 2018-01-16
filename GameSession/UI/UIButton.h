#pragma once
#include "GameSession/UI/IUIEventHandler.h"
#include "GameSession/UI/ISpriteHandler.h"
#include "GameSession/Rendering/Textures/EnumsTexture.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
enum class TextureName;
}

namespace hvgs::ui
{

/////////////////////////////////////////////////////////////////////////////

enum class ButtonState
{
	Default = 0,
	Hover,
	Pressed,
	Deactivated
};

class CUIButton :
	public IUIEventHandler
{

public:
	CUIButton();
	virtual ~CUIButton();

	virtual void Draw() const;

public:
	TextureName GetTextureForState(ButtonState state) const;
	void SetTextureForState(ButtonState state, TextureName textureName);

	const ScreenPos& GetSize() const;
	void SetSize(const ScreenPos& size);

	const ScreenPos& GetPosition() const;
	void SetPosition(const ScreenPos& position);

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
	ScreenPos m_Position = ScreenPos({ 0.0f, 0.0f });
	ScreenPos m_Size = ScreenPos({ 0.0f, 0.0f });

	ButtonState m_State = ButtonState::Default;
	bool		m_IsPressed = false;

	Map<ButtonState, TextureName> m_ButtonTextures = { {ButtonState::Default, TextureName::BUTTON_DEFAULT},
													{ButtonState::Hover, TextureName::BUTTON_HOVER},
													{ButtonState::Pressed, TextureName::BUTTON_PRESSED },
													{ButtonState::Deactivated, TextureName::BUTTON_DEACTIVATED } };

	std::function<void()> m_Action;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui

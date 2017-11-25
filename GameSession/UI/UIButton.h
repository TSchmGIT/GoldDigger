#pragma once
#include "GameSession/UI/IUIEventHandler.h"
#include "GameSession/UI/ISpriteHandler.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
enum class TextureName : hvuint8;
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
	public IUIEventHandler,
	public ISpriteHandler
{

public:
	CUIButton();
	virtual ~CUIButton();

	virtual void Draw() const override;

public:
	const ScreenPos& GetSize() const;
	void SetSize(const ScreenPos& size);

	const ScreenPos& GetPosition() const;
	void SetPosition(const ScreenPos& position);

protected:
	virtual void OnMouseClicked(const ScreenPos& pos) override;
	virtual void OnMouseMove(const ScreenPos& delta, const ScreenPos& pos) override;

	TextureName GetTextureName() const;

protected:
	ScreenPos m_Position = ScreenPos(0.0f, 0.0f);
	ScreenPos m_Size = ScreenPos(0.0f, 0.0f);

	ButtonState m_State = ButtonState::Default;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui

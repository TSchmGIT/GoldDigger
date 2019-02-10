#pragma once

/////////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

/////////////////////////////////////////////////////////////////////////////

class CUIWidget
{
public:
	CUIWidget() = default;
	virtual ~CUIWidget() = default;

public:
	const ScreenPos& GetPosition() const;
	void SetPosition(const ScreenPos& position);

	const Vector2& GetSize() const;
	void SetSize(const ScreenPos& size);

private:
	Vector2 m_Position;		///< The local position of this widget
	Vector2 m_Size;			///< The render size in pixel of this widget

};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui

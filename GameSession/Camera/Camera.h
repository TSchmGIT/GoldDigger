#pragma once

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CCamera
{

public:
	CCamera();
	virtual ~CCamera();

	void Tick();

public:
	void DrawDebug();

public:
	ScreenPos WorldToScreenPoint(const WorldPos& worldPos) const;
	ScreenPos WorldToScreenDirection(const WorldPos& worldDir) const;

	WorldPos ScreenToWorldPoint(const ScreenPos& screenPos) const;

	bool IsInView(const sf::FloatRect& worldRect) const;

public:
	const Vector2& GetPosition() const;
	void SetPosition(const Vector2& position);
	void SetPosition(Vector2&& position);

	float GetZoomFactor() const;
	void SetZoomFactor(float zoomFactor);

protected:
	void UpdateZoom();

protected:
	Vector2		m_Position;
	float		m_ZoomFactor;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

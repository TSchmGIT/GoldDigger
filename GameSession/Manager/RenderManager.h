#pragma once
#include "GameSession/Manager/SingletonBase.h"
#include "GameSession/Rendering/Fonts/EnumsFont.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class IRenderElement;
enum class TextureName : hvuint8;
}

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CRenderManager : public CSingletonBase<CRenderManager>
{

public:
	CRenderManager();
	virtual ~CRenderManager();

	void PrepareTick();

	void Init();

	void Render();

public:
	const sf::RenderWindow* GetWindow() const;
	sf::RenderWindow* GetWindow();

	hvuint GetScreenWidth() const;
	hvuint GetScreenHeight() const;

public:
	void RegisterRenderElement(const IRenderElement* renderElement);
	void UnregisterRenderElement(const IRenderElement* renderElement);

public:
	void DrawText(const ScreenPos& pos, const String& content, const FontName& fontName = FontName::Arial, unsigned int charSize = 30, const sf::Color& textColor = sf::Color::White);

	void DrawTextWorld(const WorldPos& pos, const String& content, const FontName& fontName = FontName::Arial, unsigned int charSize = 30, const sf::Color& textColor = sf::Color::White);
	/// Draws a sprite on the screen with given world coordinates (position may be out of viewport)
	void DrawSpriteWorld(const WorldPos& pos, const TextureName& textureName);

protected:
	sf::Vector2f WorldToRenderPos(Vector2 worldPos) const;

protected:
	UniquePtr<sf::RenderWindow>		m_Window;
	Vector<const IRenderElement*>	m_RenderElementList;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

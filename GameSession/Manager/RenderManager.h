#pragma once
#include "GameSession/Manager/SingletonBase.h"
#include "GameSession/Rendering/Fonts/EnumsFont.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{
class ISpriteHandler;
}

namespace hvgs
{
class IRenderElement;

enum class TextureName;

class CChunk;
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

	void Display();

public:
	const sf::RenderWindow* GetWindow() const;
	sf::RenderWindow* GetWindow();

	hvuint GetScreenWidth() const;
	hvuint GetScreenHeight() const;
	ScreenPos GetScreenCenter() const;

public:
	void RegisterRenderElement(const IRenderElement* renderElement);
	void UnregisterRenderElement(const IRenderElement* renderElement);

	void RegisterSpriteHandler(const ui::ISpriteHandler* spriteHandler);
	void UnregisterSpriteHandler(const ui::ISpriteHandler* spriteHandler);
public:
	void DrawText(const ScreenPos& pos, const String& content, Alignment alignment = Alignment::TopLeft, const FontName& fontName = FontName::Arial, unsigned int charSize = 60, const sf::Color& textColor = sf::Color::White);

	void DrawTextWorld(const WorldPos& pos, const String& content, const FontName& fontName = FontName::Arial, unsigned int charSize = 60, const sf::Color& textColor = sf::Color::White);
	/// Draws a sprite on the screen with given world coordinates (position may be out of viewport)
	void DrawSpriteWorld(const WorldPos& pos, TextureName textureName, Alignment alignment = Alignment::Center);
	void DrawSpriteWorld(const WorldPos& pos, TextureName textureName, float scaleFactor, Alignment alignment = Alignment::Center);
	void DrawSpriteWorld(const WorldPos& pos, TextureName textureName, const ScreenPos& size, Alignment alignment = Alignment::Center);
	void DrawSprite(const ScreenPos& screenPos, TextureName textureName, const ScreenPos& size, Alignment alignment = Alignment::Center);
	void DrawSprite(const ScreenPos& screenPos, TextureName textureName, Alignment alignment = Alignment::Center);

	void DrawChunk(const CChunk& chunk);

protected:
	void DrawSpriteInternal(const ScreenPos& pos, const sf::Texture* texture, const Vector2& scaleFactor = Vector2(1.0, 1.0f), Alignment alignment = Alignment::Center);

	static void AdjustPivot(ScreenPos& original, const Vector2& renderSize, Alignment alignment = Alignment::Center);
	static void AdjustPivot(ScreenPos& original, const Vector2& renderSize, const Vector2& pivot);
	static void AdjustTextPivot(sf::Text& text, Alignment alignment = Alignment::TopLeft);

	//////////////////////////////////////////////////////////////////////////
	// Debug
protected:
	void DrawRenderManager();

	void DrawBackground();

protected:
	UniquePtr<sf::RenderWindow>		m_Window;
	Set<const IRenderElement*>		m_RenderElementSet;
	Set<const ui::ISpriteHandler*>	m_SpriteHandlerSet;

	hvsdk::CObjectPool<sf::Sprite>	m_PoolSprites;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

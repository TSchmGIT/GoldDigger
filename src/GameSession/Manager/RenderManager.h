#pragma once
#include <hvsdk/Meta/ObjectPool.h>

#include "GameSession/Manager/SingletonBase.h"
#include "GameSession/Rendering/Fonts/EnumsFont.h"
#include "GameSession/Rendering/RenderDefines.h"
#include "GameSession/Rendering/Textures/EnumsTexture.h"

/////////////////////////////////////////////////////////////////////////////

namespace sf
{
class Color;
}

namespace hvgs::ui
{
class ISpriteHandler;
}

namespace hvgs
{
class IRenderElement;

class CUIScope;

class CChunk;
}

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CRenderManager : public CSingletonBase<CRenderManager>
{

public:
	CRenderManager();
	virtual ~CRenderManager() = default;

	void PrepareTick();

	void Init();

	void Render();

	void Display();

public:
	const sf::RenderWindow& GetWindow() const;

	void SetView(const sf::View& view);
	void CloseWindow();
	bool PollEvent(sf::Event& e);

	hvuint GetScreenWidth() const;
	hvuint GetScreenHeight() const;
	Vector2 GetScreenSize() const;
	ScreenPos GetScreenCenter() const;

	constexpr static int GetBaseScreenWidth() { return 1920; }
	constexpr static int GetBaseScreenHeight() { return 1080; }
	constexpr static Vector2 GetBaseScreenSize() { return { float(GetBaseScreenWidth()), float(GetBaseScreenHeight()) }; }

	void ScaleUIPos(ScreenPos& pos) const;
	void ScaleUISize(ScreenPos& pos) const;
	void ScaleUITextSize(FontSize& fontSize) const;

	const CUIScope* GetCurrentUIScope() const;
	void SetCurrentUIScope(const CUIScope* uiScope);

public:
	static void AdjustPivot(ScreenPos& original, const Vector2& renderSize, Alignment alignment = Alignment::Center);
	static void AdjustPivot(ScreenPos& original, const Vector2& renderSize, const Vector2& pivot);
	static void AdjustTextPivot(sf::Text& text, Alignment alignment = Alignment::TopLeft);

public:
	void RegisterRenderElement(const IRenderElement* renderElement);
	void UnregisterRenderElement(const IRenderElement* renderElement);

	void RegisterSpriteHandler(const ui::ISpriteHandler* spriteHandler);
	void UnregisterSpriteHandler(const ui::ISpriteHandler* spriteHandler);
public:
	void DrawTextUI(const ScreenPos& pos, const String& content, Alignment alignment = Alignment::TopLeft, const FontName& fontName = FontName::FiraSans_Regular, FontSize fontSize = FontSize(60), const sf::Color& textColor = sf::Color::White);

	void DrawTextWorld(const WorldPos& pos, const String& content, const FontName& fontName = FontName::FiraSans_Regular, FontSize charSize = FontSize(60), const sf::Color& textColor = sf::Color::White);
	/// Draws a sprite on the screen with given world coordinates (position may be out of viewport)
	void DrawSpriteWorld(const WorldPos& pos, TextureName textureName, Alignment alignment = Alignment::Center);
	void DrawSpriteWorld(const WorldPos& pos, TextureName textureName, float scaleFactor, Alignment alignment = Alignment::Center);
	void DrawSpriteWorld(const WorldPos& pos, TextureName textureName, const ScreenPos& size, Alignment alignment = Alignment::Center);
	void DrawSpriteUI(const ScreenPos& screenPos, TextureName textureName, const ScreenPos& size, Alignment alignment = Alignment::TopLeft);
	void DrawSpriteUI(const ScreenPos& screenPos, TextureName textureName, Alignment alignment = Alignment::TopLeft);

	void DrawChunk(const CChunk& chunk);

protected:
	void DrawSpriteInternal(const ScreenPos& pos, const sf::Texture* texture, const Vector2& scaleFactor = Vector2(1.0, 1.0f), Alignment alignment = Alignment::Center);

protected:
	void DrawRenderManager();

	void DrawBackground();

protected:
	sf::RenderWindow				m_Window;
	Set<const IRenderElement*>		m_RenderElementSet;
	Set<const ui::ISpriteHandler*>	m_SpriteHandlerSet;

	hvsdk::CObjectPool<sf::Sprite>	m_PoolSprites;

	const CUIScope* m_currentUIScope;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

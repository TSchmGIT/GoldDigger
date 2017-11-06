#pragma once
#include "GameSession/Manager/SingletonBase.h"
#include "GameSession/Rendering/Fonts/EnumsFont.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class IRenderElement;
enum class TextureName : hvuint8;

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

public:
	void RegisterRenderElement(const IRenderElement* renderElement);
	void UnregisterRenderElement(const IRenderElement* renderElement);

public:
	void DrawText(const ScreenPos& pos, const String& content, const FontName& fontName = FontName::Arial, unsigned int charSize = 60, const sf::Color& textColor = sf::Color::White);

	void DrawTextWorld(const WorldPos& pos, const String& content, const FontName& fontName = FontName::Arial, unsigned int charSize = 60, const sf::Color& textColor = sf::Color::White);
	/// Draws a sprite on the screen with given world coordinates (position may be out of viewport)
	void DrawSpriteWorld(const WorldPos& pos, const TextureName& textureName, Alignment alignment = Alignment::Center);

	void DrawChunk(const CChunk& chunk);

protected:
	static void AdjustSpritePivot(ScreenPos& original, const Vector2& renderSize, Alignment alignment = Alignment::Center);

	//////////////////////////////////////////////////////////////////////////
	// Debug
protected:
	void DrawRenderManager();

protected:
	UniquePtr<sf::RenderWindow>		m_Window;
	Vector<const IRenderElement*>	m_RenderElementList;

	hvsdk::CObjectPool<sf::Sprite>	m_PoolSprites;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

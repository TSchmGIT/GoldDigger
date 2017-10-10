#include "stdafx.h"
#include "RenderManager.h"

#include <SFML/Graphics/Text.hpp>

#include "GameSession/Manager/CameraManager.h"
#include "GameSession/Manager/Rendering/FontManager.h"
#include "GameSession/Manager/Rendering/TextureManager.h"
#include "GameSession/Rendering/IRenderElement.h"
#include "GameSession/Camera/Camera.h"


//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

static const int	SCREEN_WIDTH = 1536;
static const int	SCREEN_HEIGHT = 864;

//////////////////////////////////////////////////////////////////////////

CRenderManager::CRenderManager()
	: CSingletonBase()
{

}

//////////////////////////////////////////////////////////////////////////

CRenderManager::~CRenderManager()
{

}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::PrepareTick()
{
	m_Window->clear();
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::Init()
{
	CFontManager::GetMutable().Init();
	CTextureManager::GetMutable().Init();

	m_Window = std::make_unique<sf::RenderWindow>(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Gold Digger");
	//m_window->setVerticalSyncEnabled(true);
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::Render()
{
	DrawSpriteWorld(Vector2(), TextureName::Background);

	for (const IRenderElement* renderElement : m_RenderElementList)
	{
		renderElement->Draw();
	}

	m_Window->display();
}

//////////////////////////////////////////////////////////////////////////

const sf::RenderWindow* CRenderManager::GetWindow() const
{
	return m_Window.get();
}

//////////////////////////////////////////////////////////////////////////

sf::RenderWindow* CRenderManager::GetWindow()
{
	return m_Window.get();
}

//////////////////////////////////////////////////////////////////////////

hvuint CRenderManager::GetScreenWidth() const
{
	ASSERT_OR_EXECUTE(m_Window, return 0);
	return m_Window->getSize().x;
}

//////////////////////////////////////////////////////////////////////////

hvuint CRenderManager::GetScreenHeight() const
{
	ASSERT_OR_EXECUTE(m_Window, return 0);
	return m_Window->getSize().y;
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::RegisterRenderElement(const IRenderElement* renderElement)
{
	ASSERT_OR_EXECUTE(renderElement, return);
	m_RenderElementList.push_back(renderElement);
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::UnregisterRenderElement(const IRenderElement* renderElement)
{
	ASSERT_OR_EXECUTE(renderElement, return);

	auto it = std::find_if(m_RenderElementList.cbegin(), m_RenderElementList.cend(), [renderElement](const IRenderElement* element) { return renderElement == element; });
	ASSERT_OR_EXECUTE(it != m_RenderElementList.end(), return);

	m_RenderElementList.erase(it);
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::DrawText(const ScreenPos& pos, const String& content, const FontName& fontName /*= FontName::Arial*/, unsigned int charSize /*= 30*/, const sf::Color& textColor /*= sf::Color::White*/)
{
	sf::Text* text = CFontManager::GetMutable().PopText(content, fontName, charSize, textColor);
	text->setPosition(pos);

	auto globalBounds = text->getGlobalBounds();
	if (globalBounds.left + globalBounds.width < 0.0f || globalBounds.left > GetScreenWidth() ||
		globalBounds.top + globalBounds.height < 0.0f || globalBounds.top > GetScreenHeight())
	{
		CFontManager::GetMutable().PushText(text);
		return;
	}

	m_Window->draw(*text);

	CFontManager::GetMutable().PushText(text);
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::DrawTextWorld(const WorldPos& pos, const String& content, const FontName& fontName /*= FontName::Arial*/, unsigned int charSize /*= 30*/, const sf::Color& textColor /*= sf::Color::White*/)
{
	ASSERT_OR_EXECUTE(CCameraManager::GetMutable().GetActive(), return);
	ScreenPos screenPos = CCameraManager::GetMutable().GetActive()->WorldToScreenPoint(pos);

	//// Do not render objects outside the view
	//if (screenPos.x < 0 || screenPos.x > GetScreenWidth() ||
	//	screenPos.y < 0 || screenPos.y > GetScreenHeight())
	//{
	//	return;
	//}

	DrawText(screenPos, content, fontName, charSize, textColor);
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::DrawSpriteWorld(const WorldPos& pos, const TextureName& textureName)
{
	const sf::Texture* texture = CTextureManager::Get().GetTexture(textureName);
	ASSERT_OR_EXECUTE(texture, return);

	sf::Vector2u textureSize = texture->getSize();

	ASSERT_OR_EXECUTE(CCameraManager::GetMutable().GetActive(), return);
	sf::Vector2f screenPos = CCameraManager::GetMutable().GetActive()->WorldToScreenPoint(pos);

	// Do not render objects outside the view
	if (screenPos.x + textureSize.x < 0 || screenPos.x - textureSize.x > GetScreenWidth() ||
		screenPos.y + textureSize.y < 0 || screenPos.y - textureSize.y > GetScreenHeight())
	{
		return;
	}

	sf::Sprite sprite;
	sprite.setTexture(*texture);

	ASSERT_OR_EXECUTE(CCameraManager::GetMutable().GetActive(), return);
	sprite.setPosition(CCameraManager::GetMutable().GetActive()->WorldToScreenPoint(pos));

	float zoomFactor = CCameraManager::GetMutable().GetActive()->GetZoomFactor();
	sprite.setScale(zoomFactor, zoomFactor);

	m_Window->draw(std::move(sprite));
}

//////////////////////////////////////////////////////////////////////////

sf::Vector2f CRenderManager::WorldToRenderPos(Vector2 worldPos) const
{
	return sf::Vector2f(worldPos.x, worldPos.y);
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
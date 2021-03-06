#include "stdafx.h"
#include "RenderManager.h"

#include <SFML/Graphics/Text.hpp>

#include "GameSession/Camera/Camera.h"
#include "GameSession/Manager/CameraManager.h"
#include "GameSession/Manager/Rendering/FontManager.h"
#include "GameSession/Manager/Rendering/TextureManager.h"
#include "GameSession/Rendering/IRenderElement.h"
#include "GameSession/World/Chunk.h"
#include "GameSession/World/ChunkSlice.h"
#include "GameSession/World/World.h"
#include "Rendering/DebugRender.h"


//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

static const int	SCREEN_WIDTH = 3584;
static const int	SCREEN_HEIGHT = 2016;

//////////////////////////////////////////////////////////////////////////

CRenderManager::CRenderManager()
	: CSingletonBase()
	, m_PoolSprites(32, 1000)
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
	m_Window->setJoystickThreshold(0.25f);
	m_Window->setKeyRepeatEnabled(false);
	m_Window->setVerticalSyncEnabled(true);
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::Render()
{
	CWorld* world = CWorld::GetWorld();
	for (const auto& kvPair : world->GetChunks())
	{
		DrawChunk(*kvPair.second);
	}

	for (const IRenderElement* renderElement : m_RenderElementList)
	{
		renderElement->Draw();
	}

	DrawRenderManager();
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::Display()
{
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

void CRenderManager::DrawText(const ScreenPos& pos, const String& content, const FontName& fontName /*= FontName::Arial*/, unsigned int charSize /*= 60*/, const sf::Color& textColor /*= sf::Color::White*/)
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

void CRenderManager::DrawTextWorld(const WorldPos& pos, const String& content, const FontName& fontName /*= FontName::Arial*/, unsigned int charSize /*= 60*/, const sf::Color& textColor /*= sf::Color::White*/)
{
	ASSERT_OR_EXECUTE(CCameraManager::GetMutable().GetActive(), return);
	ScreenPos screenPos = CCameraManager::GetMutable().GetActive()->WorldToScreenPoint(pos);

	DrawText(screenPos, content, fontName, charSize, textColor);
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::DrawSpriteWorld(const WorldPos& pos, const TextureName& textureName, Alignment alignment /*= Alignment::Center*/)
{
	ASSERT_OR_EXECUTE(CCameraManager::GetMutable().GetActive(), return);
	Vector2 screenPos = CCameraManager::GetMutable().GetActive()->WorldToScreenPoint(pos);

	// Do not render objects outside the view
	if (screenPos.x < 0 || screenPos.x > GetScreenWidth() ||
		screenPos.y < 0 || screenPos.y > GetScreenHeight())
	{
		return;
	}

	const sf::Texture* texture = CTextureManager::Get().GetTexture(textureName);
	ASSERT_OR_EXECUTE(texture, return);

	sf::Vector2u textureSize = texture->getSize();

	// Do not render objects outside the view
	if (screenPos.x + textureSize.x < 0 || screenPos.x - textureSize.x > GetScreenWidth() ||
		screenPos.y + textureSize.y < 0 || screenPos.y - textureSize.y > GetScreenHeight())
	{
		return;
	}

	sf::Sprite* sprite = m_PoolSprites.New();
	sprite->setTexture(*texture);

	ASSERT_OR_EXECUTE(CCameraManager::Get().GetActive(), return);
	float scaleFactor = BASE_TILE_SIZE_PX / texture->getSize().x * CCameraManager::Get().GetActive()->GetZoomFactor();
	sprite->setScale(scaleFactor, scaleFactor);

	AdjustSpritePivot(screenPos, Vector2(textureSize) * scaleFactor, alignment);

	sprite->setPosition(screenPos.x, screenPos.y);

	m_Window->draw(*sprite);

	m_PoolSprites.Delete(sprite);
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::DrawChunk(const CChunk& chunk)
{
	const auto& chunkSliceMap = chunk.GetChunkSlices();


	for (const auto& kvPair : chunkSliceMap)
	{
		const auto& chunkSlice = kvPair.second;

		Vector2i csWorldPos = chunkSlice.GetWorldPos();
		sf::FloatRect chunkSliceRect(float(csWorldPos.x), float(csWorldPos.y), CHUNKSLICE_SIZE_X, CHUNKSLICE_SIZE_Y);

		if (!CCameraManager::Get().GetActive()->IsInView(chunkSliceRect))
		{
			continue;
		}


		sf::VertexArray va(sf::Quads, 4 * CHUNKSLICE_SIZE_X * CHUNKSLICE_SIZE_Y);


		for (hvuint8 x = 0; x < CHUNKSLICE_SIZE_X; x++)
		{
			for (hvuint8 y = 0; y < CHUNKSLICE_SIZE_Y; y++)
			{
				const CTile& tile = chunkSlice.GetTileAt(x, y);

				TileType tileType = tile.GetTileType();
				if (tileType == TileType::Air)
				{
					continue;
				}

				WorldPos worldPos = Vector2(float(x), float(y)) + chunkSlice.GetWorldPos();

				int index = 4 * (y + x * CHUNKSLICE_SIZE_Y);

				va[index].position = CCameraManager::Get().GetActive()->WorldToScreenPoint({ worldPos.x							, worldPos.y });
				va[index + 1].position = CCameraManager::Get().GetActive()->WorldToScreenPoint({ worldPos.x						, worldPos.y + 1 });
				va[index + 2].position = CCameraManager::Get().GetActive()->WorldToScreenPoint({ worldPos.x + 1					, worldPos.y + 1 });
				va[index + 3].position = CCameraManager::Get().GetActive()->WorldToScreenPoint({ worldPos.x + 1					, worldPos.y });

				switch (tileType)
				{
				case hvgs::TileType::Dirt:
					va[index].texCoords = { 64, 32 };
					va[index + 1].texCoords = { 64, 0 };
					va[index + 2].texCoords = { 96, 0 };
					va[index + 3].texCoords = { 96, 32 };
					break;
				case hvgs::TileType::Stone:
					va[index].texCoords = { 96, 32 };
					va[index + 1].texCoords = { 96, 0 };
					va[index + 2].texCoords = { 128, 0 };
					va[index + 3].texCoords = { 128, 32 };
					break;
				case TileType::IronOre:
					va[index].texCoords = { 160, 32 };
					va[index + 1].texCoords = { 160, 0 };
					va[index + 2].texCoords = { 192, 0 };
					va[index + 3].texCoords = { 192, 32 };
					break;
				default:
					va[index].texCoords = { 480, 512 };
					va[index + 1].texCoords = { 480, 480 };
					va[index + 2].texCoords = { 512, 480 };
					va[index + 3].texCoords = { 512, 512 };
					break;
				}
			}
		}

		m_Window->draw(va, CTextureManager::Get().GetTexture(TextureName::TileAtlas));
	}
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::AdjustSpritePivot(ScreenPos& original, const Vector2& renderSize, Alignment alignment /*= Alignment::Center*/)
{
	switch (alignment)
	{
	case hvgs::Alignment::Center:
		original += ScreenPos{ renderSize.x * -0.5f, renderSize.y * -0.5f };
		break;
	case Alignment::CenterBottom:
		original += ScreenPos{ renderSize.x * -0.5f, renderSize.y * -1.0f };
	}
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::DrawRenderManager()
{
	CCameraManager::GetMutable().GetActive()->DrawDebug();
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
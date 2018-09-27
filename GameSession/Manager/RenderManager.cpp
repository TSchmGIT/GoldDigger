#include "stdafx.h"
#include "RenderManager.h"

#include <SFML/Graphics/Text.hpp>

#include "GameSession/Camera/Camera.h"
#include "GameSession/Manager/CameraManager.h"
#include "GameSession/Manager/InteractionManager.h"
#include "GameSession/Manager/Rendering/FontManager.h"
#include "GameSession/Manager/Rendering/TextureManager.h"
#include "GameSession/Rendering/DebugRender.h"
#include "GameSession/Rendering/IRenderElement.h"
#include "GameSession/Rendering/UIScope.h"
#include "GameSession/UI/ISpriteHandler.h"
#include "GameSession/UI/Scenes/Meta/SceneManager.h"
#include "GameSession/World/Chunk.h"
#include "GameSession/World/ChunkSlice.h"
#include "GameSession/World/World.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

static const int	SCREEN_WIDTH = 1920;
static const int	SCREEN_HEIGHT = 1080;

//////////////////////////////////////////////////////////////////////////

CRenderManager::CRenderManager()
	: CSingletonBase()
	, m_PoolSprites(32, 1000)
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

	sf::Image icon;
	bool loadFromFile = icon.loadFromFile(R"(D:\Users\Thorsten\Documents\Programming\C++\Projects\GoldDigger\Resources\Textures\Actor.png)");
	ASSERT_OR_EXECUTE(loadFromFile, return);

	if (loadFromFile)
	{
		m_Window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::Render()
{
	// Background
	DrawBackground();

	for (const auto& kvPair : CWorld::Get().GetChunks())
	{
		DrawChunk(*kvPair.second);
	}

	for (const IRenderElement* renderElement : m_RenderElementSet)
	{
		renderElement->Draw();
	}

	for (const auto& spriteHandler : m_SpriteHandlerSet)
	{
		spriteHandler->Draw();
	}

	// Draw UI
	hvgs::ui::CSceneManager::Get().Draw();
	CInteractionManager::Get().Draw();

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
	return m_Window->getSize().x;
}

//////////////////////////////////////////////////////////////////////////

hvuint CRenderManager::GetScreenHeight() const
{
	return m_Window->getSize().y;
}

//////////////////////////////////////////////////////////////////////////

hvgs::ScreenPos CRenderManager::GetScreenCenter() const
{
	return ScreenPos(m_Window->getSize()) * 0.5f;
}

//////////////////////////////////////////////////////////////////////////

const hvgs::CUIScope* CRenderManager::GetCurrentUIScope() const
{
	return m_currentUIScope;
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::SetCurrentUIScope(const CUIScope* uiScope)
{
	m_currentUIScope = uiScope;
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::RegisterRenderElement(const IRenderElement* renderElement)
{
	ASSERT_OR_EXECUTE(renderElement, return);
	m_RenderElementSet.emplace(renderElement);
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::UnregisterRenderElement(const IRenderElement* renderElement)
{
	ASSERT_OR_EXECUTE(renderElement, return);

	auto it = m_RenderElementSet.find(renderElement);
	ASSERT_OR_EXECUTE(it != m_RenderElementSet.end(), return);

	m_RenderElementSet.erase(it);
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::RegisterSpriteHandler(const ui::ISpriteHandler* spriteHandler)
{
	ASSERT_OR_EXECUTE(spriteHandler, return);
	m_SpriteHandlerSet.emplace(spriteHandler);
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::UnregisterSpriteHandler(const ui::ISpriteHandler* spriteHandler)
{
	ASSERT_OR_EXECUTE(spriteHandler, return);

	auto it = m_SpriteHandlerSet.find(spriteHandler);
	ASSERT_OR_EXECUTE(it != m_SpriteHandlerSet.end(), return);

	m_SpriteHandlerSet.erase(it);
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::DrawText(const ScreenPos& pos, const String& content, Alignment alignment /*= Alignment::TopLeft*/, const FontName& fontName /*= FontName::Arial*/, FontSize fontSize /*= 60*/, const sf::Color& textColor /*= sf::Color::White*/)
{
	ScreenPos screenPosScoped = pos;
	if (const auto* uiScope = GetCurrentUIScope(); uiScope)
	{
		screenPosScoped += uiScope->GetPivotPosition();
	}

	sf::Text* text = CFontManager::GetMutable().PopText(content, fontName, fontSize, textColor);

	AdjustTextPivot(*text, alignment);
	text->setPosition(screenPosScoped);

	auto globalBounds = text->getGlobalBounds();
	if (globalBounds.left + globalBounds.width < 0.0f || globalBounds.left > GetScreenWidth() ||
		globalBounds.top + globalBounds.height < 0.0f || globalBounds.top > GetScreenHeight())
	{
		CFontManager::GetMutable().PushText(text);
		return;
	}

#ifdef DEBUG_RENDER_TEXT
	Vector2 rectSize(text->getGlobalBounds().width, text->getGlobalBounds().height);
	DrawSpriteUI(screenPosScoped + ScreenPos(text->getLocalBounds().left, text->getLocalBounds().top), TextureName::WHITE, rectSize, alignment);
	text->setFillColor(sf::Color::Black);
	m_Window->draw(*text);
#else
	m_Window->draw(*text);
#endif

	CFontManager::GetMutable().PushText(text);
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::DrawTextWorld(const WorldPos& pos, const String& content, const FontName& fontName /*= FontName::Arial*/, FontSize charSize /*= FontSize(60)*/, const sf::Color& textColor /*= sf::Color::White*/)
{
	ASSERT_OR_EXECUTE(CCameraManager::GetMutable().GetActive(), return);
	ScreenPos screenPos = CCameraManager::GetMutable().GetActive()->WorldToScreenPoint(pos);

	DrawText(screenPos, content, Alignment::TopLeft, fontName, charSize, textColor);
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::DrawSpriteWorld(const WorldPos& pos, TextureName textureName, Alignment alignment /*= Alignment::Center*/)
{
	ASSERT_OR_EXECUTE(CCameraManager::GetMutable().GetActive(), return);
	Vector2 screenPos = CCameraManager::GetMutable().GetActive()->WorldToScreenPoint(pos);

	const sf::Texture* texture = CTextureManager::Get().GetTexture(textureName);
	ASSERT_OR_EXECUTE(texture, return);

	float scaleFactor = BASE_TILE_SIZE_PX / float(texture->getSize().x) * CCameraManager::Get().GetActive()->GetZoomFactor();
	DrawSpriteInternal(screenPos, texture, { scaleFactor, scaleFactor }, alignment);
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::DrawSpriteWorld(const WorldPos& pos, TextureName textureName, const ScreenPos& size, Alignment alignment /*= Alignment::Center*/)
{
	ASSERT_OR_EXECUTE(CCameraManager::GetMutable().GetActive(), return);
	Vector2 screenPos = CCameraManager::GetMutable().GetActive()->WorldToScreenPoint(pos);

	const sf::Texture* texture = CTextureManager::Get().GetTexture(textureName);
	ASSERT_OR_EXECUTE(texture, return);

	// Calculate scale that should be applied to the texture (min scale of x and y dimension)
	Vector2 textureSize = texture->getSize();
	ASSERT_OR_EXECUTE(textureSize.x > 0 && textureSize.y > 0, return);
	Vector2 scale(size.x / textureSize.x, size.y / textureSize.y);

	DrawSpriteInternal(screenPos, texture, scale, alignment);
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::DrawSpriteWorld(const WorldPos& pos, TextureName textureName, float scaleFactor, Alignment alignment /*= Alignment::Center*/)
{
	const auto* camera = CCameraManager::Get().GetActive();
	ASSERT_OR_EXECUTE(camera, return);
	Vector2 screenPos = camera->WorldToScreenPoint(pos);

	const sf::Texture* texture = CTextureManager::Get().GetTexture(textureName);
	ASSERT_OR_EXECUTE(texture, return);

	scaleFactor *= camera->GetZoomFactor();

	DrawSpriteInternal(screenPos, texture, { scaleFactor, scaleFactor }, alignment);
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::DrawSpriteUI(const ScreenPos& screenPos, TextureName textureName, const ScreenPos& size, Alignment alignment /*= Alignment::TopLeft*/)
{
	ScreenPos screenPosScoped = screenPos;
	if (const auto* uiScope = GetCurrentUIScope(); uiScope)
	{
		screenPosScoped += uiScope->GetPivotPosition();
	}
	
	// Do not render objects outside the view
	if (screenPosScoped.x < 0 || screenPosScoped.x > GetScreenWidth() ||
		screenPosScoped.y < 0 || screenPosScoped.y > GetScreenHeight())
	{
		return;
	}

	const sf::Texture* texture = CTextureManager::Get().GetTexture(textureName);
	ASSERT_OR_EXECUTE(texture, return);

	// Calculate scale that should be applied to the texture (min scale of x and y dimension)
	Vector2 textureSize = texture->getSize();
	ASSERT_OR_EXECUTE(textureSize.x > 0 && textureSize.y > 0, return);
	Vector2 scale(size.x / textureSize.x, size.y / textureSize.y);

	DrawSpriteInternal(screenPosScoped, texture, scale, alignment);
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::DrawSpriteUI(const ScreenPos& screenPos, TextureName textureName, Alignment alignment /*= Alignment::TopLeft*/)
{
	ScreenPos screenPosScoped = screenPos;
	if (const auto* uiScope = GetCurrentUIScope(); uiScope)
	{
		screenPosScoped += uiScope->GetPivotPosition();
	}

	// Do not render objects outside the view
	if (screenPosScoped.x < 0 || screenPosScoped.x > GetScreenWidth() ||
		screenPosScoped.y < 0 || screenPosScoped.y > GetScreenHeight())
	{
		return;
	}

	const sf::Texture* texture = CTextureManager::Get().GetTexture(textureName);
	ASSERT_OR_EXECUTE(texture, return);

	DrawSpriteInternal(screenPosScoped, texture, { 1.0f, 1.0f }, alignment);
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::DrawChunk(const CChunk& chunk)
{
	auto&& chunkSliceMap = chunk.GetChunkSlices();


	for (auto&& kvPair : chunkSliceMap)
	{
		auto&& chunkSlice = kvPair.second;

		Vector2i csWorldPos = chunkSlice->GetWorldPos();
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
				const CTile& tile = chunkSlice->GetTileAt(x, y);

				TileType tileType = tile.GetTileType();
				if (tileType == TileType::Air)
				{
					continue;
				}

				WorldPos worldPos = Vector2(float(x), float(y)) + chunkSlice->GetWorldPos();

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

		m_Window->draw(va, CTextureManager::Get().GetTexture(TextureName::TILEATLAS));
	}
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::DrawSpriteInternal(const ScreenPos& pos, const sf::Texture* texture, const Vector2& scaleFactor /*= Vector2(1.0, 1.0f)*/, Alignment alignment /*= Alignment::Center*/)
{
	ASSERT_OR_EXECUTE(texture, return);

	sf::Vector2u textureSize = texture->getSize();

	// Do not render objects outside the view
	if (pos.x + textureSize.x < 0 || pos.x - textureSize.x > GetScreenWidth() ||
		pos.y + textureSize.y < 0 || pos.y - textureSize.y > GetScreenHeight())
	{
		return;
	}

	sf::Sprite* sprite = m_PoolSprites.New();
	sprite->setTexture(*texture);
	sprite->setScale(scaleFactor);

	Vector2 screenPosAdjusted = pos;
	AdjustPivot(screenPosAdjusted, Vector2::Scale(textureSize, scaleFactor), alignment);

	sprite->setPosition(screenPosAdjusted.x, screenPosAdjusted.y);

	m_Window->draw(*sprite);

	m_PoolSprites.Delete(sprite);

}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::AdjustPivot(ScreenPos& original, const Vector2& renderSize, Alignment alignment /*= Alignment::Center*/)
{
	switch (alignment)
	{
	case Alignment::TopLeft: /* no adjustments to original */
		AdjustPivot(original, renderSize, Vector2(0.0f, 0.0f));
		return;
	case Alignment::Left:
		AdjustPivot(original, renderSize, Vector2(0.0f, 0.5f));
		break;
	case Alignment::BottomLeft:
		AdjustPivot(original, renderSize, Vector2(0.0f, 1.0f));
		break;

	case Alignment::CenterTop:
		AdjustPivot(original, renderSize, Vector2(0.5f, 0.0f));
		break;
	case hvgs::Alignment::Center:
		AdjustPivot(original, renderSize, Vector2(0.5f, 0.5f));
		break;
	case Alignment::CenterBottom:
		AdjustPivot(original, renderSize, Vector2(0.5f, 1.0f));
		break;

	case Alignment::TopRight:
		AdjustPivot(original, renderSize, Vector2(1.0f, 0.0f));
		break;
	case Alignment::Right:
		AdjustPivot(original, renderSize, Vector2(1.0f, 0.5f));
		break;
	case Alignment::BottomRight:
		AdjustPivot(original, renderSize, Vector2(1.0f, 1.0f));
		original += ScreenPos{ renderSize.x * -1.0f, renderSize.y * -1.0f };
		break;
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::AdjustPivot(ScreenPos& original, const Vector2& renderSize, const Vector2& pivot)
{
	original += ScreenPos::Scale(renderSize, -pivot);
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::AdjustTextPivot(sf::Text& text, Alignment alignment /*= Alignment::TopLeft*/)
{
	auto bounds = text.getLocalBounds();
	Vector2 size(bounds.width, bounds.height);

	Vector2 newOrigin(0.0f, 0.0f);

	switch (alignment)
	{
	case Alignment::TopLeft:
		/* no adjustments to original */
		break;
	case Alignment::Left:
		newOrigin += Vector2::Scale(size, Vector2{ 0.0f, 0.5f });

		newOrigin.y += bounds.top * 0.5f;
		break;
	case Alignment::BottomLeft:
		newOrigin += Vector2::Scale(size, Vector2{ 0.0f, 1.0f });

		newOrigin.y += bounds.top;
		break;

	case Alignment::CenterTop:
		newOrigin += Vector2::Scale(size, Vector2{ 0.5f, 0.0f });

		newOrigin.x += bounds.left * 0.5f;
		break;
	case hvgs::Alignment::Center:
		newOrigin += Vector2::Scale(size, Vector2{ 0.5f, 0.5f });

		newOrigin.x += bounds.left * 0.5f;
		newOrigin.y += bounds.top * 0.5f;
		break;
	case Alignment::CenterBottom:
		newOrigin += Vector2::Scale(size, Vector2{ 0.5f, 1.0f });

		newOrigin.x += bounds.left * 0.5f;
		newOrigin.y += bounds.top;
		break;

	case Alignment::TopRight:
		newOrigin += Vector2::Scale(size, Vector2{ 1.0f, 0.0f });

		newOrigin.x += bounds.left;
		break;
	case Alignment::Right:
		newOrigin += Vector2::Scale(size, Vector2{ 1.0f, 0.5f });

		newOrigin.x += bounds.left;
		newOrigin.y += bounds.top * 0.5f;
		break;
	case Alignment::BottomRight:
		newOrigin += Vector2::Scale(size, Vector2{ 1.0f, 1.0f });

		newOrigin.x += bounds.left;
		newOrigin.y += bounds.top;
		break;
	default:
		break;
	}

	text.setOrigin(newOrigin);
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::DrawRenderManager()
{
	CCameraManager::GetMutable().GetActive()->DrawDebug();
}

//////////////////////////////////////////////////////////////////////////

void CRenderManager::DrawBackground()
{
	DrawSpriteWorld({ 0.0f, 0.0f }, TextureName::BACKGROUND_SPACE, 1.0f, Alignment::BottomLeft);
	DrawSpriteWorld({ 2160.0f / BASE_TILE_SIZE_PX, 0.0f }, TextureName::BACKGROUND_SPACE, 1.0f, Alignment::BottomLeft);
	DrawSpriteWorld({ 2160.0f * 2.0f / BASE_TILE_SIZE_PX, 0.0f }, TextureName::BACKGROUND_SPACE, 1.0f, Alignment::BottomLeft);
	DrawSpriteWorld({ 2160.0f * 3.0f / BASE_TILE_SIZE_PX, 0.0f }, TextureName::BACKGROUND_SPACE, 1.0f, Alignment::BottomLeft);

	DrawSpriteWorld({ -2160.0f / BASE_TILE_SIZE_PX, 0.0f }, TextureName::BACKGROUND_SPACE, 1.0f, Alignment::BottomLeft);
	DrawSpriteWorld({ -2160.0f * 2.0f / BASE_TILE_SIZE_PX, 0.0f }, TextureName::BACKGROUND_SPACE, 1.0f, Alignment::BottomLeft);
	DrawSpriteWorld({ -2160.0f * 3.0f / BASE_TILE_SIZE_PX, 0.0f }, TextureName::BACKGROUND_SPACE, 1.0f, Alignment::BottomLeft);
	DrawSpriteWorld({ -2160.0f * 4.0f / BASE_TILE_SIZE_PX, 0.0f }, TextureName::BACKGROUND_SPACE, 1.0f, Alignment::BottomLeft);
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
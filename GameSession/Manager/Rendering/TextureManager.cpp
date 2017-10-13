#include "stdafx.h"
#include "TextureManager.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

static const String RESOURCES_PATH_TEXTURES("..\\Resources\\Textures\\");

//////////////////////////////////////////////////////////////////////////

CTextureManager::CTextureManager()
{

}

//////////////////////////////////////////////////////////////////////////

CTextureManager::~CTextureManager()
{

}

//////////////////////////////////////////////////////////////////////////

void CTextureManager::Init()
{
	for (size_t i = 0; i < size_t(TextureName::Count); i++)
	{
		TextureName textureName = TextureName(i);

		std::string fileName = RESOURCES_PATH_TEXTURES;

		switch (textureName)
		{
		case TextureName::Actor:
			fileName += "Actor.png";
			break;
		case TextureName::Background:
			fileName += "background.png";
			break;
		case TextureName::TileAtlas:
			fileName += "TileAtlas/Final_Atlas.png";
			break;
		default:
			break;
		}

		sf::Texture texture;
		if (!texture.loadFromFile(fileName))
		{
			LOG_ERROR("Could not load texture with filename " << fileName);
			continue;
		}

		m_TextureTable.emplace(std::move(textureName), std::move(texture));
	}

}

//////////////////////////////////////////////////////////////////////////

const sf::Texture* CTextureManager::GetTexture(TextureName textureName) const
{
	auto it = m_TextureTable.find(textureName);
	ASSERT_OR_EXECUTE(it != m_TextureTable.end(), return nullptr);
	return &it->second;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs

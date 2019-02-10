#pragma once
#include "GameSession/Manager/SingletonBase.h"
#include "GameSession/Rendering/Textures/EnumsTexture.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CTextureManager : public CSingletonBase<CTextureManager>
{

public:
	CTextureManager() = default;
	virtual ~CTextureManager() = default;

	void Init();

public:
	const sf::Texture* GetTexture(TextureName textureName) const;

protected:
	Map<TextureName, UniquePtr<sf::Texture>> m_TextureTable;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

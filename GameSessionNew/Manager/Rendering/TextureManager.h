#pragma once
#include "GameSessionNew/Manager/SingletonBase.h"
#include "GameSessionNew/Rendering/Textures/EnumsTexture.h"

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
	Map<TextureName, sf::Texture> m_TextureTable;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

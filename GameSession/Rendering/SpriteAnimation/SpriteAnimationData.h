#pragma once
#include "GameSession/Rendering/Textures/EnumsTexture.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CSpriteAnimationData
{

public:
	CSpriteAnimationData();
	virtual ~CSpriteAnimationData();

public:
	float GetSpeedFactor() const;
	void SetSpeedFactor(float speedFactor);

	TextureName GetSpriteAtlas() const;
	void SetSpriteAtlas(TextureName textureName);

protected:
	float			m_BasePlaybackSpeed = 1.0f / 15.0f;
	float			m_SpeedFactor = 1.0f;
	TextureName		m_SpriteAtlas = TextureName::INVALID;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

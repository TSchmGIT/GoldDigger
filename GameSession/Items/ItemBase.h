#pragma once

#include "GameSession/Rendering/Textures/EnumsTexture.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CItemBase
{

public:
	CItemBase() = default;
	virtual ~CItemBase() = default;

public:
	virtual String GetDisplayName() const;
	virtual TextureName GetTextureName() const = 0;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

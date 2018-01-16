#pragma once

#include "GameSession/Physics/CollisionObject.h"
#include "GameSession/Rendering/Textures/EnumsTexture.h"
#include "GameSession/Rendering/IRenderElement.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CBuildingBase
	: public ICollisionObject
	, public IRenderElement
{
public:
	CBuildingBase() = default;
	virtual ~CBuildingBase() = default;

	virtual void Draw() const override;

public:
	Layer GetLayer() const final;

	const WorldPos& GetPosition() const;
	void SetPosition(const WorldPos& position);

	TextureName GetTexture() const;
	void SetTexture(TextureName value);

	const Vector2& GetSize() const;
	void SetSize(const Vector2& value);

protected:
	virtual WorldPos GetAABBOrigin() const override;
	virtual WorldPos GetAABBHalfs() const override;

protected:
	//////////////////////////////////////////////////////////////////////////
	// Visuals
	TextureName	m_Texture = TextureName::INVALID;

	//////////////////////////////////////////////////////////////////////////
	// Logic
	WorldPos m_Position = WorldPos(0.0f, 0.0f);
	Vector2 m_Size = Vector2(1.0f, 1.0f);
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

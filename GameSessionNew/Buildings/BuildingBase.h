#pragma once

#include "GameSessionNew/Physics/CollisionObject.h"
#include "GameSessionNew/Rendering/Textures/EnumsTexture.h"
#include "GameSessionNew/Rendering/IRenderElement.h"

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

	const Vector2& GetSize() const;
	void SetSize(const Vector2& value);

protected:
	virtual TextureName GetBuildingTexture() const = 0;

	virtual WorldPos GetAABBOrigin() const override;
	virtual WorldPos GetAABBHalfs() const override;

private:
	//////////////////////////////////////////////////////////////////////////
	// Logic
	WorldPos m_Position = WorldPos(0.0f, 0.0f);
	Vector2 m_Size = Vector2(1.0f, 1.0f);
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

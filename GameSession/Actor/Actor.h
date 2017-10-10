#pragma once

#include "GameSession/GameObjects/IGameObject.h"
#include "GameSession/Rendering/IRenderElement.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CActor : public IRenderElement, public IGameObject
{

public:
	CActor();
	virtual ~CActor();

public: // IGameObject
	virtual void Tick() override;

public: // IRenderElement
	virtual void Draw() const override;

public:
	Vector2 GetPosition() const;
	void SetPosition(const Vector2& position);
protected:
	Vector2		m_Position;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
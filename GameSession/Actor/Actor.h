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

protected:
	Vector2		m_Position;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

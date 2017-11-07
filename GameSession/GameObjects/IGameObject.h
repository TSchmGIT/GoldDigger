#pragma once

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class IGameObject
{

public:
	IGameObject();
	IGameObject(const IGameObject& other);
	IGameObject(IGameObject&& other);

	IGameObject& operator=(const IGameObject& other);
	IGameObject& operator=(IGameObject&& other);
	virtual ~IGameObject();

	virtual void PrepareTick() {};
	virtual void Tick() {};
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

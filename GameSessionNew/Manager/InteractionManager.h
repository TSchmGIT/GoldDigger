#pragma once
#include "GameSessionNew/Manager/SingletonBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class IInteractionObject;
}

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CInteractionManager : public CSingletonBase<CInteractionManager>
{

public:
	CInteractionManager();
	virtual ~CInteractionManager();

	void Tick();
	void Draw() const;

public:
	void RegisterInteractionObject(IInteractionObject* collisionObject);
	void UnregisterInteractionObject(IInteractionObject* collisionObject);

	const Set<IInteractionObject*>& GetInteractionObjects() const;

protected:
	Set<IInteractionObject*> m_InteractionObjectSet;

};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

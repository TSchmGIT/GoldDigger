#pragma once
#include "GameSession/Manager/SingletonBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CGameManager : public CSingletonBase<CGameManager>
{

public:
	CGameManager();
	virtual ~CGameManager();

public:
	void Init();
	void Shutdown();

	void Run();

protected:
	void PrepareTick();

	void PollEvents();

protected:
	sf::RenderWindow m_GameWindow;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

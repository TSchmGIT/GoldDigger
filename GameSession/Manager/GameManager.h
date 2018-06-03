#pragma once
#include "GameSession/Manager/SingletonBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class CWorld;
}

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CGameManager : public CSingletonBase<CGameManager>
{

public:
	CGameManager();
	virtual ~CGameManager();

public:
	void Construct();

	void Shutdown();

	void Run();

protected:
	void Init();
	void InitAfterCreation();

	void PrepareTick();

	void PollEvents();

	void Tick();

	void Render();

protected:
	void Draw() const;

	sf::RenderWindow	m_GameWindow;
	UniquePtr<CWorld>	m_World = std::make_unique<CWorld>();
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

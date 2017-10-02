#pragma once
#include "GameSession/Manager/SingletonBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CRenderManager : public CSingletonBase<CRenderManager>
{

public:
	CRenderManager();
	virtual ~CRenderManager();

	void Init();

public:
	const sf::RenderWindow* GetWindow() const;
	sf::RenderWindow* GetWindow();

public:
	void DrawText(std::string text);

protected:
	UniquePtr<sf::RenderWindow> m_window;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

// GoldDigger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <hvmath/Vector2/Vector2.inl>

#include "GameSession/Actor/Actor.h"
#include "GameSession/Manager/GameManager.h"
#include "GameSession/Manager/RenderManager.h"
#include "GameSession/World/World.h"

using namespace hvgs;

CActor GetRenderElement()
{
	return CActor();
}

int main()
{
	std::srand(unsigned int(std::time(nullptr)));

	CGameManager::GetMutable().Init();

	CActor actor;
	actor.SetPosition({ 0, 0 });
	CWorld world;

	CGameManager::GetMutable().Run();

	CGameManager::GetMutable().Shutdown();
	boost::unordered_map<int, int> foo;
	return 0;
}
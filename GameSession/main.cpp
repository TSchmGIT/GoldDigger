// GoldDigger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <hvmath/Vector2/Vector2.inl>

#include "GameSession/Actor/Actor.h"
#include "GameSession/Manager/GameManager.h"
#include "GameSession/Manager/RenderManager.h"

using namespace hvgs;

CActor GetRenderElement()
{
	return CActor();
}

int main()
{
	CGameManager::GetMutable().Init();

	CActor actor;
	actor.SetPosition(Vector2(0.0f, 420.0f));

	CGameManager::GetMutable().Run();

	CGameManager::GetMutable().Shutdown();
	boost::unordered_map<int, int> foo;
	return 0;
}
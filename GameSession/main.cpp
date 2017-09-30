// GoldDigger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "GameSession/Manager/GameManager.h"
#include "GameSession/Manager/RenderManager.h"

using namespace hvgs;

int main()
{
	CGameManager::GetMutable().Init();

	CGameManager::GetMutable().Run();

	CGameManager::GetMutable().Shutdown();
	boost::unordered_map<int, int> foo;
	return 0;
}
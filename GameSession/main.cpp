// GoldDigger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <hvmath/Physics/AABB.h>

#include "GameSession/Actor/Actor.h"
#include "GameSession/Manager/GameManager.h"
#include "GameSession/Manager/RenderManager.h"
#include "GameSession/World/World.h"
#include "UI/UIButton.h"

using namespace hvgs;

int main()
{
	std::srand(unsigned int(std::time(nullptr)));

	CGameManager::GetMutable().Init();

	CWorld world;

	ui::CUIButton button;
	button.SetPosition({ 100, 100 });
	button.SetSize({ 100, 100 });

	CGameManager::GetMutable().Run();

	CGameManager::GetMutable().Shutdown();
	return 0;
}
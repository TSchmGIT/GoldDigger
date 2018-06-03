// GoldDigger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <hvmath/Physics/AABB.h>

#include "GameSession/Actor/Actor.h"
#include "GameSession/Manager/GameManager.h"
#include "GameSession/Manager/RenderManager.h"
#include "GameSession/World/World.h"
#include "GameSession/UI/UIButton.h"
#include "GameSession/UI/Scenes/Meta/SceneManager.h"
#include "GameSession/UI/Scenes/Meta/SceneEnum.h"

using namespace hvgs;

int main()
{
	std::srand(unsigned int(std::time(nullptr)));

	CGameManager::GetMutable().Construct();

	CGameManager::GetMutable().Run();

	CGameManager::GetMutable().Shutdown();

	return 0;
}
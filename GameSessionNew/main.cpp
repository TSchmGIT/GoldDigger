// GoldDigger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <hvmath/Physics/AABB.h>

#include "GameSessionNew/Actor/Actor.h"
#include "GameSessionNew/Manager/GameManager.h"
#include "GameSessionNew/Manager/RenderManager.h"
#include "GameSessionNew/World/World.h"
#include "GameSessionNew/UI/Elements/UIButton.h"
#include "GameSessionNew/UI/Scenes/Meta/SceneManager.h"
#include "GameSessionNew/UI/Scenes/Meta/SceneEnum.h"
#include "Rendering/UIScope.h"

using namespace hvgs;

int main()
{
	std::srand(unsigned int(std::time(nullptr)));

	CGameManager::GetMutable().Construct();

	CGameManager::GetMutable().Run();

	CGameManager::GetMutable().Shutdown();

	return 0;
}
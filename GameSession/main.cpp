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

	CGameManager::GetMutable().Init();

	CWorld world;
	world.Construct();

	ui::CUIButton button;
	button.SetPosition(ScreenPos({ 100.0f, 100.0f }));
	button.SetSize(ScreenPos({ 100.0f, 100.0f }));
	button.SetAction([]() { hvgs::ui::CSceneManager::GetMutable().ToggleState(hvgs::ui::SceneID::Inventory); });

	CGameManager::GetMutable().Run();

	CGameManager::GetMutable().Shutdown();
	return 0;
}
// GoldDigger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "GameSession/Manager/GameManager.h"
#include "GameSession/Manager/RenderManager.h"
#include <hvmath/Vector2/Vector2.inl>

using namespace hvgs;

int main()
{
	hvmath::CVector2<int> vecInt(1, 4);
	Vector2f vecFloat(1.2f, 5.5f);

	hvmath::CVector2<int> vecIntAdd(3, 5);
	hvmath::CVector2<float> vecFloatAdd(2.5f, 10.5f);

	CGameManager::GetMutable().Init();

	CGameManager::GetMutable().Run();

	CGameManager::GetMutable().Shutdown();
	boost::unordered_map<int, int> foo;
	return 0;
}
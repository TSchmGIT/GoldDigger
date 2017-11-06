// GoldDigger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <hvmath/Physics/AABB.h>

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

	// Create world
	CWorld world;

	// Create actor
	CActor actor;
	actor.SetPosition({ 0, 0 });

	/*hvmath::AABB aabb1{ { 0.0f, 0.0f }, { 0.5f, 0.5f } };
	hvmath::AABB aabb2{ { 1.5f, 0.0f }, { 0.5f, 0.5f } };

	hvmath::Sweep sweep;
	hvmath::AABB collider;

	bool collideAABB1 = aabb1.SweepInto({ aabb2 }, Vector2(-2.0f, 0.0f), sweep, collider);
	bool collideAABB2 = aabb2.SweepInto({ aabb1 }, Vector2(-2.0f, 0.0f), sweep, collider);
	collideAABB1 = collideAABB2;*/

	CGameManager::GetMutable().Run();

	CGameManager::GetMutable().Shutdown();
	boost::unordered_map<int, int> foo;
	return 0;
}
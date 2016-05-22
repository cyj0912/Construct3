#include "Game.h"
#include <SFMT.h>
#include <Windows.h>

C3_NAMESPACE_BEGIN
FGame Game;

void FGame::NewGame() {
	ScreenSize = RC.Render->GetMainCamera()->HalfVecGivenZ(0);
	Entities.push_back(&Player);
	Entities.push_back(new FEnemy);
	for (IEntity* Entity : Entities) {
		Entity->Init();
	}
	GameTimer.Init();
	LARGE_INTEGER l;
	QueryPerformanceCounter(&l);
	sfmt_init_gen_rand(&RandGen, l.LowPart ^ l.HighPart);
	LastEnemySpawnTime = GameTimer.GetTotalTime();
}

void FGame::EndGame() {
	for (IEntity* Entity : Entities) {
		Entity->Destroy();
	}
	Entities.clear();
}

void FGame::Update() {
	RC.System->GetSystemClock()->Tick();
	GameTimer.Tick();
	float CurTime = GameTimer.GetTotalTime();
	float LastEnemySpawnDelta = CurTime - LastEnemySpawnTime;
	if (LastEnemySpawnDelta > 0.8) {
		LastEnemySpawnTime = CurTime;
		Entities.push_back(new FEnemy);
		Entities.back()->Init();
	}
	for (IEntity* Entity : Entities) {
		Entity->Update();
	}
	ScreenSize = RC.Render->GetMainCamera()->HalfVecGivenZ(0);
}
C3_NAMESPACE_END

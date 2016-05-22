#include "Game.h"
#include <SFMT.h>
#include <Windows.h>

C3_NAMESPACE_BEGIN
FGame Game;

void FGame::NewGame() {
	InGame = true;
	ScreenSize = RC.Render->GetMainCamera()->HalfVecGivenZ(0);
	Entities.push_back(&Player);
	for (IEntity* Entity : Entities) {
		Entity->Init();
	}
	RC.System->GetSystemClock()->Init();
	//GameTimer.Init();
	LARGE_INTEGER l;
	QueryPerformanceCounter(&l);
	sfmt_init_gen_rand(&RandGen, l.LowPart ^ l.HighPart);
	LastEnemySpawnTime = GameTimer.GetTotalTime() + 2;	//2 second delay on start of game
}

void FGame::EndGame() {
	InGame = false;
	for (IEntity* Entity : Entities) {
		Entity->Destroy();
	}
	Entities.clear();
	RC.System->GetSystemClock()->SwitchPause();
}

void FGame::Update() {
	if (InGame) {
		RC.System->GetSystemClock()->Tick();
		GameTimer.Tick();
		float CurTime = GameTimer.GetTotalTime();
		float LastEnemySpawnDelta = CurTime - LastEnemySpawnTime;
		if (LastEnemySpawnDelta > 0.8) {
			LastEnemySpawnTime = CurTime;
			Entities.push_back(new FEnemy);
			Entities.back()->Init();
		}
		for (ActiveEntity = 0; ActiveEntity < Entities.size(); ActiveEntity++) {
			Entities.at(ActiveEntity)->Update();

			//Check if player died
			if (!InGame) {
				return;
			}
		}
		ScreenSize = RC.Render->GetMainCamera()->HalfVecGivenZ(0);
	}
}

void FGame::KillActiveEntity() {
	Entities.at(ActiveEntity)->Destroy();
	Entities.erase(Entities.begin() + ActiveEntity);
}
C3_NAMESPACE_END

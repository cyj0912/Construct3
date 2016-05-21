#pragma once
#include <Core.h>
#include <Controls.h>
#include <Entity.h>

C3_NAMESPACE_BEGIN
class FGame {
public:
	FTimer<FPerfTimer> GameTimer;
	std::vector<IEntity*> Entities;
	FControls ActiveControls;

	FGame() : GameTimer(*RC.System->GetSystemClock()) {

	}

	void NewGame() {
		Entities.push_back(new FPlayer);
		for (IEntity* Entity : Entities) {
			Entity->Init();
		}
		GameTimer.Init();
	}
	
	void EndGame() {
		Entities.clear();
	}

	void Update() {
		RC.System->GetSystemClock()->Tick();
		GameTimer.Tick();
		for (IEntity* Entity : Entities) {
			Entity->Update();
		}
	}

	void Test() {

	}
};

extern FGame Game;
C3_NAMESPACE_END

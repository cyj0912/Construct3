#pragma once
#include <Core.h>
#include <Controls.h>

C3_NAMESPACE_BEGIN
class FGame {
private:
	FTimer<FPerfTimer> GameTimer;

public:
	FControls ActiveControls;

	FGame() : GameTimer(*RC.System->GetSystemClock()) {

	}

	void Init() {

	}

	void Update() {
		RC.System->GetSystemClock()->Tick();
		GameTimer.Tick();
	}

	void Test() {

	}
};

extern FGame Game;
C3_NAMESPACE_END

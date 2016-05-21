#pragma once
#include <Core.h>
C3_NAMESPACE_BEGIN
class FGame {
private:
	FTimer<FPerfTimer> GameTimer;

public:
	FGame() : GameTimer(*RC.System->GetSystemClock())
	{

	}

	void Init() {

	}

	void Update() {
		RC.System->GetSystemClock()->Tick();
		GameTimer.Tick();
	}
};
C3_NAMESPACE_END

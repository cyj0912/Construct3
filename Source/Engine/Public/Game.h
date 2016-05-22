#pragma once
#include <Core.h>
#include <Controls.h>
#include <Entity.h>
#include <random>
#include <time.h>
#include <IRender.h>
#include <SFMT.h>

C3_NAMESPACE_BEGIN
extern SGCamera* mainCam;
class FGame {
public:
	FTimer<FPerfTimer> GameTimer;
	std::vector<IEntity*> Entities;
	FControls ActiveControls;
	FPlayer Player;
	sfmt_t RandGen;
	glm::vec2 ScreenSize;
	float LastEnemySpawnTime;
	uint32_t FrameCount;
	uint64_t ActiveEntity;
	bool InGame;

	FGame() : GameTimer(*RC.System->GetSystemClock()), FrameCount(0) {

	}

	void NewGame();
	
	void EndGame();

	void Update();

	void KillActiveEntity();
};

extern FGame Game;
C3_NAMESPACE_END

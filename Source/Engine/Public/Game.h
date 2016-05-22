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

	FGame() : GameTimer(*RC.System->GetSystemClock()) {

	}

	void NewGame();
	
	void EndGame();

	void Update();
};

extern FGame Game;
C3_NAMESPACE_END

#include <Entity.h>
#include <Game.h>
#include <OpenGL3Render/Public/Render.h>
#include <Engine.h>
#include <SFMT.h>

C3_NAMESPACE_BEGIN
//Player
void FPlayer::Init() {
	SGEntry = RC.Render->NewSGObject();
	SGEntry->LoadModelFromResource(RC.Engine->BunnyRMesh);
}

void FPlayer::Destroy() {
	SGEntry->DeleteModel();
}

void FPlayer::Update() {
	const float Speed = 18;
	const float SpeedUpOverTime = 0.05;
	const float Movement =
		Game.GameTimer.GetDeltaTime() * Speed
		+ SpeedUpOverTime * Game.GameTimer.GetTotalTime();
	if (Game.ActiveControls.MoveUp) {
		SGEntry->Move(0, Movement, 0);
	}
	if (Game.ActiveControls.MoveDown) {
		SGEntry->Move(0, -Movement, 0);
	}
	if (Game.ActiveControls.MoveLeft) {
		SGEntry->Move(-Movement, 0, 0);
	}
	if (Game.ActiveControls.MoveRight) {
		SGEntry->Move(Movement, 0, 0);
	}
}

//Enemy
void FEnemy::Init() {
	SGEntry = RC.Render->NewSGObject();
	SGEntry->LoadModelFromResource(RC.Engine->BunnyRMesh);
	float XMove = sfmt_genrand_real1(&Game.RandGen) * Game.ScreenSize.x * 2 - Game.ScreenSize.x;
	float YMove = sfmt_genrand_real1(&Game.RandGen) * Game.ScreenSize.y * 2 - Game.ScreenSize.y;
	SGEntry->Move(XMove, YMove, -20);
}

void FEnemy::Destroy() {
	SGEntry->DeleteModel();
}

void FEnemy::Update() {
	const float Speed = 3;
	const float SpeedUpOverTime = 0.05;
	const float Movement =
		Game.GameTimer.GetDeltaTime() * Speed
		+ SpeedUpOverTime * Game.GameTimer.GetTotalTime();
	SGEntry->Move(0, 0, Movement);
}
C3_NAMESPACE_END
#include <Entity.h>
#include <Game.h>
#include <OpenGL3Render/Public/Render.h>
#include <Engine.h>

C3_NAMESPACE_BEGIN
//Player
void FPlayer::Init() {
	SGEntry = RC.Render->NewSGObject();
	SGEntry->LoadModelFromResource(RC.Engine->BunnyRMesh);
}

void FPlayer::Update() {
	const float speed = 18;
	if (Game.ActiveControls.MoveUp) {
		SGEntry->Move(0, Game.GameTimer.GetDeltaTime() * speed, 0);
	}
	if (Game.ActiveControls.MoveDown) {
		SGEntry->Move(0, Game.GameTimer.GetDeltaTime() * -speed, 0);
	}
	if (Game.ActiveControls.MoveLeft) {
		SGEntry->Move(Game.GameTimer.GetDeltaTime() * -speed, 0, 0);
	}
	if (Game.ActiveControls.MoveRight) {
		SGEntry->Move(Game.GameTimer.GetDeltaTime() * speed, 0, 0);
	}
}

//Enemy
void FEnemy::Init() {
	SGEntry = RC.Render->NewSGObject();
	SGEntry->LoadModelFromResource(RC.Engine->BunnyRMesh);
	SGEntry->Move(20, 0, -20);	//Make it look smaller than the player
}

void FEnemy::Update() {
	const float speed = 1;
	SGEntry->Move(Game.GameTimer.GetDeltaTime() * -speed, 0, 0);
}
C3_NAMESPACE_END
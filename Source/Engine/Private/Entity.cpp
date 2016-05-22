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

void FPlayer::Destroy() {
	SGEntry->DeleteModel();
}

void FPlayer::Update() {
	const float speed = 18.0f;
	glm::vec3 move(0.0f);
	if (Game.ActiveControls.MoveUp) {
		move.y += 1.0f;
	}
	if (Game.ActiveControls.MoveDown) {
		move.y -= 1.0f;
	}
	if (Game.ActiveControls.MoveLeft) {
		move.x -= 1.0f;
	}
	if (Game.ActiveControls.MoveRight) {
		move.x += 1.0f;
	}
	if (move.x != 0.0f || move.y != 0.0f)
	{
		move = glm::normalize(move) * speed * Game.GameTimer.GetDeltaTime();
		SGEntry->Move(move);
	}
}

//Enemy
void FEnemy::Init() {
	SGEntry = RC.Render->NewSGObject();
	SGEntry->LoadModelFromResource(RC.Engine->BunnyRMesh);
	SGEntry->Move(20, 0, -20);	//Make it look smaller than the player
}

void FEnemy::Destroy() {
	SGEntry->DeleteModel();
}

void FEnemy::Update() {
	const float speed = 1;
	SGEntry->Move(Game.GameTimer.GetDeltaTime() * -speed, 0, 0);
}
C3_NAMESPACE_END
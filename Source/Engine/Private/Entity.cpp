#include <Entity.h>
#include <Game.h>
#include <OpenGL3Render/Public/Render.h>
#include <Engine.h>
#include <SFMT.h>

C3_NAMESPACE_BEGIN
const FBoundingRect& IEntity::GetBoundingRect()
{
	if(Game.FrameCount == 0 || LastBoundingUpdate < Game.FrameCount)
	{
		BoundingRect = &SGEntry->GetBoundingRectXY();
		LastBoundingUpdate = Game.FrameCount;
	}
	return *BoundingRect;
}

//Player
void FPlayer::Init() {
	SGEntry = RC.Render->NewSGObject();
	SGEntry->LoadModelFromResource(RC.Engine->BunnyRMesh);
	Health = 100;
}

void FPlayer::Destroy() {
	SGEntry->DeleteModel();
}

void FPlayer::Update() {
	if (Health <= 0) {
		Game.EndGame();
		return;
	}
	const float Speed = 18;
	const float SpeedUpOverTime = 0.03;
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
	FBoundingRect PlayerBox = GetBoundingRect();
	glm::vec2 adjust = -Game.ScreenSize - PlayerBox.BtmLeft;
	if (adjust.x < 0) {
		adjust.x = 0;
	}
	if (adjust.y < 0) {
		adjust.y = 0;
	}
	SGEntry->Move(adjust.x, adjust.y, 0);
	adjust = Game.ScreenSize - PlayerBox.TopRight;
	if (adjust.x > 0) {
		adjust.x = 0;
	}
	if (adjust.y > 0) {
		adjust.y = 0;
	}
	SGEntry->Move(adjust.x, adjust.y, 0);
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
	const float SpeedUpOverTime = 0.03;
	const float Movement =
		Game.GameTimer.GetDeltaTime() * Speed
		+ SpeedUpOverTime * Game.GameTimer.GetTotalTime();
	SGEntry->Move(0, 0, Movement);
	if (SGEntry->GetPosition().z >= 0) {
		Game.KillActiveEntity();
		Game.Player.Health -= 10;
	}
	SGEntry->SetRotation(glm::quat(glm::vec3(Game.GameTimer.GetTotalTime(), 0.0f, 1.0f)));

}
C3_NAMESPACE_END
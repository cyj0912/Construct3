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
	if (Game.ActiveControls.MoveUp) {
		SGEntry->Move(0, 1, 0);
	}
}
C3_NAMESPACE_END
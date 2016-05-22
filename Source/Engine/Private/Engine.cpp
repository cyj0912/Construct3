#include <Core.h>
#include "Engine.h"
#include "Game.h"
C3_NAMESPACE_BEGIN
void FEngine::Update()
{
	RC.System->GetSystemClock()->Tick();
}

void FEngine::Init() {
	BunnyRMesh = new RMesh("bunny.fbx");
	BunnyRMesh->LoadMesh();
}
C3_NAMESPACE_END

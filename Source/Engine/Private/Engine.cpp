#include "Engine.h"
#include "System.h"
#include "Scene.h"

C3_NAMESPACE_BEGIN

FEngine::FEngine()
{
}

FEngine::~FEngine()
{
}

void FEngine::Update()
{
	RuntimeContext.System->GetSystemClock()->Tick();
    Scene->Update();
}

void FEngine::Test()
{
    Scene = new EScene;
    Scene->Spawn();
}

C3_NAMESPACE_END

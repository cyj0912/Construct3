#include <Core.h>
#include "Engine.h"
#include "Scene.h"
C3_NAMESPACE_BEGIN
FEngine::FEngine()
{
    FLog::Debug("Construct 3 Engine");
    FLog::Debug("Version 0.1");
}

FEngine::~FEngine()
{
}

void FEngine::Update()
{
	RC.System->GetSystemClock()->Tick();
    Scene->Update();
    GetEntityManager().ReleaseMemory();
}

void FEngine::Test()
{
    Scene = GetEntityManager().NewEntity<EScene>();
    Scene->Spawn();
}

FEntityManager &FEngine::GetEntityManager()
{
    return EntityManager;
}
C3_NAMESPACE_END

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

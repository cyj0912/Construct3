#include "Scene.h"
#include "Actor.h"
#include "Component.h"
#include "Camera.h"
#include "Engine.h"
C3_NAMESPACE_BEGIN
EScene::EScene()
{
}

EScene::~EScene()
{
}

void EScene::Spawn(FEntityRef parent)
{
    EEntity::Spawn(parent);
    EActor* a = RuntimeContext.Engine->GetEntityManager().NewEntity<EActor>();
    a->Spawn(this);

    CTransform* ct = RuntimeContext.Engine->GetEntityManager().NewEntity<CTransform>();
    a->AttachComponent(ct);
    a->PrintCompInfo();

	ECamera* cam = RuntimeContext.Engine->GetEntityManager().NewEntity<ECamera>();
	cam->Spawn(this);
	cam->PrintCompInfo();
}

void EScene::Update()
{
    EEntity::Update();
}
C3_NAMESPACE_END

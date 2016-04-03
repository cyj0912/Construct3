#include "Scene.h"
#include "Actor.h"
#include "Component.h"
#include "Camera.h"
#include "Engine.h"
C3_NAMESPACE_BEGIN
C3_DEFINE_ENTITY(EScene)

EScene::EScene()
{
}

EScene::~EScene()
{
}

void EScene::Spawn(FEntityRef parent)
{
    EEntity::Spawn(parent);
    if(parent == nullptr)
        this->SetParent(this);

    EActor* a = RC.Engine->GetEntityManager().NewEntity<EActor>();
    a->Spawn(this);

    CTransform* ct = RC.Engine->GetEntityManager().NewEntity<CTransform>();
    a->AttachComponent(ct);
    a->PrintCompInfo();

	ECamera* cam = RC.Engine->GetEntityManager().NewEntity<ECamera>();
	cam->Spawn(this);
	cam->PrintCompInfo();
}

void EScene::Update()
{
    EEntity::Update();
}
C3_NAMESPACE_END

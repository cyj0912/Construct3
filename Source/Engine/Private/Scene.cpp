#include "Scene.h"
#include "Actor.h"
#include "Component.h"
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
    EActor* a = new EActor;
    a->Spawn(this);

    CTransform* ct = new CTransform;
    a->AttachComponent(ct);

    a->PrintCompInfo();
}

void EScene::Update()
{
    EEntity::Update();
}
C3_NAMESPACE_END

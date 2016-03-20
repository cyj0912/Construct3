#include "Entity.h"

C3_NAMESPACE_BEGIN

EEntity::EEntity()
{
}

EEntity::~EEntity()
{
}

void EEntity::Spawn(FEntityRef parent)
{
    ParentEntity = parent;
}

void EEntity::Update()
{
    for(auto ent : ChildEntities)
    {
        ent->Update();
    }
}

void EEntity::Kill()
{
    for(auto ent : ChildEntities)
    {
        ent->Kill();
    }
}

C3_NAMESPACE_END

#include "Entity.h"
#include "Component.h"

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
        delete ent;
    }
}

void EEntity::AttachComponent(FEntityRef ref)
{
    TypeId id = typeid(ref).hash_code();
    Components[id] = ref;
}

FEntityRef EEntity::GetComponent(TypeId typeId)
{
    if(Components.find(typeId) != Components.end())
        return Components[typeId];
    return nullptr;
}

void EEntity::DetachComponent(TypeId typeId)
{
    Components.erase(typeId);
}

C3_NAMESPACE_END

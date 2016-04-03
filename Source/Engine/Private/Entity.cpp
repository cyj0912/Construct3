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
    for(auto ent : ChildEntities)
    {
        ent->Spawn(this);
    }
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

void EEntity::AddChild(FEntityRef child)
{
    ChildEntities.insert(child);
}

void EEntity::RemoveChild(FEntityRef child)
{
    ChildEntities.erase(child);
}

C3_NAMESPACE_END

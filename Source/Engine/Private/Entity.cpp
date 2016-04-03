#include "Entity.h"
#include "Component.h"

#include <sstream>
#include <Log.h>
C3_NAMESPACE_BEGIN
C3_DEFINE_ENTITY(EEntity)

EEntity::EEntity()
{
}

EEntity::~EEntity()
{
    for(auto ent : ChildEntities)
    {
        if(ent->GetParent() == this)
            ent->SetParent(nullptr);
    }
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

void EEntity::PrintCompInfo()
{
    for(auto i : Components)
    {
        std::stringstream ss;
        ss << i.first << " " << i.second;
        FLog::Debug(ss.str().c_str());
    }
}

FEntityRef EEntity::GetParent()
{
    return ParentEntity;
}

void EEntity::SetParent(FEntityRef parent)
{
    ParentEntity = parent;
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

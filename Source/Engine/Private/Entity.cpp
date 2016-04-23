#include "Entity.h"
#include "Component.h"

#include <sstream>
#include <Log.h>
C3_NAMESPACE_BEGIN
C3_DEFINE_ENTITY(EEntity)

void FCompContainer::AttachComponent(FEntityRef ref)
{
    TypeId id = typeid(ref).hash_code();
    Components[id] = ref;
}

FEntityRef FCompContainer::GetComponent(TypeId typeId)
{
    if(Components.find(typeId) != Components.end())
        return Components[typeId];
    return nullptr;
}

void FCompContainer::DetachComponent(TypeId typeId)
{
    Components.erase(typeId);
}

void FCompContainer::PrintCompInfo()
{
    for(auto i : Components)
    {
        std::stringstream ss;
        ss << "Id:" << i.first << ", Add:" << i.second.operator->();
        FLog::Debug(ss.str().c_str());
    }
}

EEntity::EEntity()
{
}

EEntity::~EEntity()
{
}

void EEntity::Spawn(FEntityRef parent)
{
}

void EEntity::Update()
{
}

void EEntity::Kill()
{
}

bool EEntity::ShouldRelease()
{
	return false;
}

C3_NAMESPACE_END

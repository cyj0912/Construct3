#include "Entity.h"
#include "Component.h"

#include <sstream>
#include <Log.h>
C3_NAMESPACE_BEGIN

void FHasComponents::AttachComponent(FEntityRef ref)
{
    TypeId id = typeid(ref).hash_code();
    Components[id] = ref;
}

FEntityRef FHasComponents::GetComponent(TypeId typeId)
{
    if(Components.find(typeId) != Components.end())
        return Components[typeId];
    return nullptr;
}

void FHasComponents::DetachComponent(TypeId typeId)
{
    Components.erase(typeId);
}

void FHasComponents::PrintCompInfo()
{
    for(auto i : Components)
    {
        std::stringstream ss;
        ss << "Id:" << i.first << ", Add:" << i.second.operator->();
        FLog::Debug(ss.str().c_str());
    }
}

C3_DEFINE_ENTITY(EEntity)

EEntity::EEntity()
{
}

EEntity::~EEntity()
{
}

void EEntity::Spawn(FEntityRef parent)
{
	SetParent(parent);
	if(parent != nullptr)
		parent->AddChild(this);
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

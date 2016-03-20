#include "Entity.h"
#include "Component.h"

C3_NAMESPACE_BEGIN

EEntity::EEntity()
{
}

bool EEntity::HasComponent(TypeId iid)
{
    for(auto iter = Components.begin(); iter != Components.end(); ++iter)
    {
        if((*iter)->IsType(iid))
            return true;
    }
    return false;
}

bool EEntity::QueryComponent(TypeId iid, void **outPtr)
{
    for(auto iter = Components.begin(); iter != Components.end(); ++iter)
    {
        if((*iter)->QueryInterface(iid, outPtr))
            return true;
    }
    return false;
}

bool EEntity::RegisterComponent(IComponent *pCom)
{
    Components.push_back(pCom);
    return true;
}

bool EEntity::DisableComponent(TypeId iid)
{
    throw "Unimplemented";
}

bool EEntity::EnableComponent(TypeId iid)
{
    throw "Unimplemented";
}

bool EEntity::RemoveComponent(TypeId iid)
{
    throw "Unimplemented";
}

C3_NAMESPACE_END

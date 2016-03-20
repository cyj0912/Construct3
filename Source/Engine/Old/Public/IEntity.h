#pragma once
#include <Core.h>
#include "TypeId.h"

C3_NAMESPACE_BEGIN

class IComponent;

/*
 * Comment: I don't think it should have ref counting
 */
class IEntity
{
public:
    virtual ~IEntity() {}
    virtual bool HasComponent(TypeId iid) = 0;
    virtual bool QueryComponent(TypeId iid, void** outPtr) = 0;
    virtual bool RegisterComponent(IComponent* pCom) = 0;
    virtual bool DisableComponent(TypeId iid) = 0;
    virtual bool EnableComponent(TypeId iid) = 0;
    virtual bool RemoveComponent(TypeId iid) = 0;
};

typedef IEntity* EntityRef;

C3_NAMESPACE_END

#pragma once

#include <Core.h>
#include <vector>

C3_NAMESPACE_BEGIN

class EEntity;

using FEntityRef = EEntity*;

class EEntity
{
public:
    EEntity();
    virtual ~EEntity();
    virtual void Spawn(FEntityRef parent = nullptr);
    virtual void Update();
    virtual void Kill();

protected:
    FEntityRef ParentEntity;
    std::vector<FEntityRef> ChildEntities;
};

C3_NAMESPACE_END

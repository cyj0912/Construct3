#pragma once
#include <Core.h>
#include "TypeId.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include <sstream>
#include <Log.h>

C3_NAMESPACE_BEGIN

class EEntity;

using FEntityRef = EEntity*; //Just in case if we use custom allocator in the future

class EEntity
{
public:
    EEntity();
    virtual ~EEntity();
    virtual void Spawn(FEntityRef parent = nullptr);
    virtual void Update();
    virtual void Kill();
    void AttachComponent(FEntityRef ref);
    FEntityRef GetComponent(TypeId typeId);
    void DetachComponent(TypeId typeId);
    void PrintCompInfo()
    {
        for(auto i : Components)
        {
            std::stringstream ss;
            ss << i.first << " " << i.second;
            FLog::Debug(ss.str().c_str());
        }
    }

    void AddChild(FEntityRef child);
    void RemoveChild(FEntityRef child);

protected:
    FEntityRef ParentEntity;
    std::unordered_set<FEntityRef> ChildEntities;
    std::unordered_map<TypeId, FEntityRef> Components;
};

C3_NAMESPACE_END

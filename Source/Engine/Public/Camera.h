#pragma once
#include <Core.h>
#include "Actor.h"
C3_NAMESPACE_BEGIN
class ECamera : public EActor
{
public:
    ECamera();
    virtual void Spawn(FEntityRef parent) override;
    virtual void Update() override
    {
        EEntity::Update();
    }
    virtual void Kill() override;
};
C3_NAMESPACE_END

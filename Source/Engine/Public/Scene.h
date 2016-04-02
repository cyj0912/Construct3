#pragma once
#include "Entity.h"

C3_NAMESPACE_BEGIN

class EScene : public EEntity
{
public:
    EScene();
    ~EScene();
    virtual void Spawn(FEntityRef parent) override;
    virtual void Update() override;
};

C3_NAMESPACE_END

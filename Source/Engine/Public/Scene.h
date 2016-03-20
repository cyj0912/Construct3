#pragma once
#include "Entity.h"

C3_NAMESPACE_BEGIN

class EScene : public EEntity
{
public:
    EScene();
    ~EScene();
    virtual void Update();
};

C3_NAMESPACE_END

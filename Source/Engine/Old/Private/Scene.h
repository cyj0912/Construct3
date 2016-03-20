#pragma once
#include "Entity.h"

C3_NAMESPACE_BEGIN

class EScene : public EEntity
{
public:
    EScene();
    ~EScene();

    std::vector<EEntity*> ChildEntities;
};

C3_NAMESPACE_END

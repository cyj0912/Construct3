#pragma once
#include <Core.h>
#include "Entity.h"
#include <string>

C3_NAMESPACE_BEGIN

class EActor : public EEntity
{
public:
    EActor();
    EActor(const std::string& name);
    const std::string& GetName();
    void SetName(const std::string& name);
private:
    std::string Name;
};

C3_NAMESPACE_END

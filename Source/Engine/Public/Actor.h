#pragma once
#include <Core.h>
#include "Entity.h"
#include <string>

C3_NAMESPACE_BEGIN

class EActor : public EEntity, public FCompContainer
{
public:
    EActor();
    const std::string& GetName() const;
    void SetName(const std::string& name);
private:
    std::string Name;
};

C3_NAMESPACE_END

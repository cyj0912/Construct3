#pragma once
#include <Core.h>
#include "Entity.h"
#include <string>
#include <tuple>

C3_NAMESPACE_BEGIN

class AActor : public EEntity, public FHasComponents
{
	C3_DECLARE_ENTITY(AActor)
    friend class FMetaEntityAActor;
public:
    AActor();
    const std::string& GetName() const;
    void SetName(const std::string& name);
private:
    std::string Name;
};

C3_NAMESPACE_END

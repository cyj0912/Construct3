#pragma once
#include <Core.h>
#include "TypeId.h"
#include <vector>
C3_NAMESPACE_BEGIN
class EEntity;
extern template void* GetNewInstance<EEntity>();
class EActor;
extern template void* GetNewInstance<EActor>();
class ECamera;
extern template void* GetNewInstance<ECamera>();

class FEntityManager
{
public:
    EEntity* NewEntity(TypeId id);

    template <typename T> T* NewEntity()
    {
        T* p = static_cast<T*>(GetNewInstance<T>());
        AllocatedEntities.push_back(p);
        return p;
    }

    void ReleaseMemory();
private:
    std::vector<EEntity*> AllocatedEntities;
};
C3_NAMESPACE_END

#include "EntityManager.h"
#include "Entity.h"
C3_NAMESPACE_BEGIN
EEntity* FEntityManager::NewEntity(c3::TypeId id)
{
    return nullptr;
}

void FEntityManager::ReleaseMemory()
{
    for(EEntity* p : AllocatedEntities)
    {
        delete p;
    }
}
C3_NAMESPACE_END

#include "EntityManager.h"
#include "Entity.h"
#include <unordered_map>
C3_NAMESPACE_BEGIN
FEntityInfo* EntityInfoList = nullptr;

EEntity* FEntityManager::NewEntity(TypeId id)
{
	static bool initialized = false;
	static std::unordered_map<size_t, FEntityInfo*> EntityInfoMap;
	if(!initialized)
	{
		initialized = true;
		FEntityInfo* curr = EntityInfoList;
		while(curr != nullptr)
		{
			EntityInfoMap[curr->ThisClass] = curr;
			curr = curr->Next;
		}
	}
	std::unordered_map<size_t, FEntityInfo*>::const_iterator resultIter;
	resultIter = EntityInfoMap.find(id);
	if (resultIter == EntityInfoMap.end())
		return nullptr;
	return (EEntity*)resultIter->second->Factory();
}

void FEntityManager::ReleaseMemory()
{
    for(EEntity* p : AllocatedEntities)
    {
		if (p->ShouldRelease())
			delete p;
    }
}
C3_NAMESPACE_END

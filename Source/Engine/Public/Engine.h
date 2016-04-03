#pragma once
#include <Core.h>
#include "EntityManager.h"
#include "Entity.h"

C3_NAMESPACE_BEGIN
class FEngine
{
public:
    FEngine();
    ~FEngine();
    void Update();
	void Test();
	FEntityManager& GetEntityManager();

private:
    FEntityManager EntityManager;
    FEntityRef Scene;
};

C3_NAMESPACE_END

#pragma once
#include <Core.h>
#include "Factory.h"
#include "Entity.h"

C3_NAMESPACE_BEGIN
class FEngine
{
public:
    FEngine();
    ~FEngine();
    void Update();
	void Test();

private:
    FFactory Factory;
    FEntityRef Scene;
};

C3_NAMESPACE_END

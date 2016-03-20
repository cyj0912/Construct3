#pragma once
#include <Core.h>
#include <IEngine.h>
#include "Factory.h"

C3_NAMESPACE_BEGIN
class FEngine : public IEngine
{
public:
    FEngine();
    ~FEngine();
	void Test();

private:
    FFactory Factory;
};

C3_NAMESPACE_END

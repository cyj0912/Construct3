#include "Engine.h"
#include "Component.h"

C3_NAMESPACE_BEGIN

IEngine* ConstructEngine()
{
    return new FEngine;
}

FEngine::FEngine()
{
}

FEngine::~FEngine()
{
}

void FEngine::Test()
{
	IUnknown* a = new CMovable;
	//Factory.RegisterComponent<IMovable, CMovable>();
}

C3_NAMESPACE_END

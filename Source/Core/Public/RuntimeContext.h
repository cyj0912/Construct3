#pragma once
#include <Namespace.h>

class FEngineLoader;

C3_NAMESPACE_BEGIN
class FSystem;
class FEngine;
class IRender;
struct FRuntimeContext
{
	void Construct();
	FSystem* System;
	FEngineLoader* Loader;
    FEngine* Engine;
	IRender* Render;
};

extern FRuntimeContext RuntimeContext;

C3_NAMESPACE_END

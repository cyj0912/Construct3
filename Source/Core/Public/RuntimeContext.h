#pragma once
#include <Namespace.h>

class FEngineLoader;

C3_NAMESPACE_BEGIN
class FSystem;
class FEngine;
class IRender;
class IEditor;
struct FRuntimeContext
{
	void Construct();
	FSystem* System;
	FEngineLoader* Loader;
    FEngine* Engine;
	IRender* Render;
	IEditor* Editor;
};

extern FRuntimeContext RC;

C3_NAMESPACE_END

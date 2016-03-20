#pragma once

class FEngineLoader;

namespace c3
{

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

}

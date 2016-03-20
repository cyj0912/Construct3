#include "EngineLoader.h"
#include <RuntimeContext.h>
#include <System.h>

FEngineLoader EngineLoader;

FEngineLoader::FEngineLoader()
{
}

FEngineLoader::~FEngineLoader()
{
}

void FEngineLoader::SetRootDirectory(const char* dir)
{
	c3::RuntimeContext.Construct();
	c3::RuntimeContext.System->Init();
	c3::RuntimeContext.System->SetRootDirectory(dir);
}

void FEngineLoader::InitEngine()
{
    Engine = new c3::FEngine;
    c3::RuntimeContext.Engine = Engine;
}

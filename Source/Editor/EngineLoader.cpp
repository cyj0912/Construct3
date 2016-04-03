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
	c3::RC.Construct();
	c3::RC.System->Init();
	c3::RC.System->SetRootDirectory(dir);
}

void FEngineLoader::InitEngine()
{
    Engine = new c3::FEngine;
    c3::RC.Engine = Engine;
}

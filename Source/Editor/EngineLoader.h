#pragma once
#include <string>
#include <Engine.h>

class FEngineLoader
{
public:
    FEngineLoader();
    ~FEngineLoader();

    void SetRootDirectory(const char* dir);
    void InitEngine();
    
private:
    c3::FEngine* Engine;
};

extern FEngineLoader EngineLoader;

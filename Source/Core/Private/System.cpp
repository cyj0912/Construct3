#include "System.h"
C3_NAMESPACE_BEGIN
FSystem::FSystem()
{
}

void FSystem::Init()
{
	SystemClock.Init();
}

void FSystem::SetRootDirectory(const char* dir)
{
	RootDirectory = std::string(dir);
}

FPerfTimer* FSystem::GetSystemClock()
{
	return &SystemClock;
}

C3_NAMESPACE_END

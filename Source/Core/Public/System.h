#pragma once
#include "Core.h"
#include "Clock.h"
#include <string>
C3_NAMESPACE_BEGIN
class FSystem
{
public:
	FSystem()
	{
	}
	void Init()
	{
		SystemClock.Init();
	}
	void SetRootDirectory(const char* dir);
	FPerfTimer* GetSystemClock()
	{
		return &SystemClock;
	}

public:
	std::string RootDirectory;
	FPerfTimer SystemClock;
};
C3_NAMESPACE_END

#pragma once
#include "Namespace.h"
#include "Clock.h"
#include <string>
C3_NAMESPACE_BEGIN
class FSystem
{
public:
	FSystem();

	void Init();
	void SetRootDirectory(const char* dir);
	FPerfTimer* GetSystemClock();

public:
	std::string RootDirectory;
	FPerfTimer SystemClock;
};
C3_NAMESPACE_END

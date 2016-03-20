#include "System.h"
C3_NAMESPACE_BEGIN

void FSystem::SetRootDirectory(const char* dir)
{
	RootDirectory = std::string(dir);
}

C3_NAMESPACE_END
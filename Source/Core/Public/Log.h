#pragma once
#include <Namespace.h>
#include <string>
C3_NAMESPACE_BEGIN
class FLog
{
public:
	static std::string ReadBuffer();
	static void Debug(const char* msg);
};
C3_NAMESPACE_END

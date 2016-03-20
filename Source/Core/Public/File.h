#pragma once
#include <Namespace.h>
#include <string>
#include <fstream>
C3_NAMESPACE_BEGIN
class FFile
{
public:
	FFile(std::string identifier);
	void Open();
	void Close();
	int BufferRead(char* buffer, int size);
	static std::string GetPhysicalPath(const std::string& identifier);
private:
	std::fstream File;
};
C3_NAMESPACE_END

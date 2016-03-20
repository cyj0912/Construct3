#include "File.h"
#include "System.h"
#include "RuntimeContext.h"
C3_NAMESPACE_BEGIN

FFile::FFile(std::string identifier)
{
	std::string& rd = static_cast<FSystem*>(RuntimeContext.System)->RootDirectory;
	File = std::fstream(rd + "/Data/" + identifier);
}

void FFile::Open()
{
}

void FFile::Close()
{
	File.close();
}

int FFile::BufferRead(char* buffer, int size)
{
	std::string str = std::string(std::istreambuf_iterator<char>(File), std::istreambuf_iterator<char>());
	strcpy(buffer, str.c_str());
	return 1;
}

std::string FFile::GetPhysicalPath(const std::string& identifier)
{
	std::string& rd = static_cast<FSystem*>(RuntimeContext.System)->RootDirectory;
	return rd + "/Data/" + identifier;
}

C3_NAMESPACE_END

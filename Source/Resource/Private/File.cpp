#include "File.h"
C3_NAMESPACE_BEGIN
RFile::RFile()
{

}

RFile::RFile(const std::string &identifier)
{
    std::string& rd = static_cast<FSystem*>(RuntimeContext.System)->RootDirectory;
    File = std::fstream(rd + "/Data/" + identifier);
}

void RFile::Open()
{
}

void RFile::Close()
{
    File.close();
}

int RFile::BufferRead(char* buffer, int size)
{
    std::string str = std::string(std::istreambuf_iterator<char>(File), std::istreambuf_iterator<char>());
    strcpy(buffer, str.c_str());
    return 1;
}

std::string RFile::GetPhysicalPath(const std::string& identifier)
{
    std::string& rd = static_cast<FSystem*>(RuntimeContext.System)->RootDirectory;
    return rd + "/Data/" + identifier;
}
C3_NAMESPACE_END

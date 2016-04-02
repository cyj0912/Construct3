#pragma once
#include <Core.h>
#include "Resource.h"
#include <string>
#include <fstream>
C3_NAMESPACE_BEGIN
class RFile : public RResource
{
public:
    RFile();
    RFile(const std::string& identifier);
    void Open();
    void Close();
    int BufferRead(char* buffer, int size);
    static std::string GetPhysicalPath(const std::string& identifier);

private:
    std::fstream File;
};
C3_NAMESPACE_END

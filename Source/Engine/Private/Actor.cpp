#include "Actor.h"
#include <cstdlib>
#include <ctime>
C3_NAMESPACE_BEGIN
C3_DEFINE_ENTITY(AActor)

class FMetaEntityAActor
{
public:
    FMetaEntityAActor()
    {
        auto NameList = { "Name" };
        auto PropList = std::make_tuple(&AActor::Name);
    }
};

void GenRandomString(std::string& buffer, int len)
{
    std::srand((unsigned int) std::time(nullptr));
    static const char candidates[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for(int i = 0; i < len; i++)
    {
        buffer.push_back(candidates[std::rand() % sizeof(candidates)]);
    }
}

AActor::AActor()
{
    std::string buf;
    GenRandomString(buf, 8);
    Name = "actor." + buf;
}

const std::string& AActor::GetName() const
{
    return Name;
}

void AActor::SetName(const std::string &name)
{
    Name = name;
}
C3_NAMESPACE_END

#include "Actor.h"
#include <cstdlib>
#include <ctime>
C3_NAMESPACE_BEGIN
C3_DEFINE_ENTITY(EActor)

void GenRandomString(std::string& buffer, int len)
{
    std::srand(std::time(nullptr));
    static const char candidates[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for(int i = 0; i < len; i++)
    {
        buffer.push_back(candidates[std::rand() % sizeof(candidates)]);
    }
}

EActor::EActor()
{
    std::string buf;
    GenRandomString(buf, 8);
    Name = "actor." + buf;
}

EActor::EActor(const std::string& name)
{
    Name = name;
}

const std::string& EActor::GetName()
{
    return Name;
}

void EActor::SetName(const std::string &name)
{
    Name = name;
}
C3_NAMESPACE_END

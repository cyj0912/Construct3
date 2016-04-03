#include "Actor.h"
C3_NAMESPACE_BEGIN
template<> void* GetNewInstance<EActor>()
{
    return new EActor;
}

EActor::EActor()
{
    Name = std::string("unnamed_actor");
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

#include "Component.h"
C3_NAMESPACE_BEGIN
CComponent::CComponent()
{
}

template<> void* GetNewInstance<CTransform>()
{
    return new CTransform;
}

C3_NAMESPACE_END

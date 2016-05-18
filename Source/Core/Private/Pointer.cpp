#include "Pointer.h"
C3_NAMESPACE_BEGIN
FRefCount::FRefCount() : RefCount(1)
{
}

FRefCount::~FRefCount()
{}

void FRefCount::AddRef()
{
    RefCount++;
}

void FRefCount::Release()
{
    auto c = RefCount--;
    if(c == 0)
        delete this;
}
C3_NAMESPACE_END

#pragma once
#include <Core.h>
#include <vector>
C3_NAMESPACE_BEGIN
class RResource
{
protected:
    virtual ~RResource();
public:
    RResource();
    void AddRef();
    void Release();
    RResource* GetParent() const;
    void SetParent(RResource *parent);
protected:
    int RefCount;
    RResource* Parent;
};
C3_NAMESPACE_END

#pragma once
#include <Core.h>
C3_NAMESPACE_BEGIN
class RResource : public FRefCount
{
protected:
    virtual ~RResource();
public:
    RResource();
    RResource* GetParent() const;
    void SetParent(RResource *parent);
protected:
    RResource* Parent;
};
C3_NAMESPACE_END

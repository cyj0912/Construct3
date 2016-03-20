#pragma once
#include <Core.h>
C3_NAMESPACE_BEGIN
/*
 * This interface should never be used
 */
class IUnknown
{
protected:
	~IUnknown()
	{
	}

public:
    virtual void AddRef() = 0;
    virtual void Release() = 0;
    virtual bool QueryInterface(TypeId iid, void** outPtr) = 0;
};
C3_NAMESPACE_END

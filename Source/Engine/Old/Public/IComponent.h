#pragma once
#include <Core.h>
#include "TypeId.h"
#include "IUnknown.h"

C3_NAMESPACE_BEGIN

class IComponent : public IUnknown
{
public:
	virtual ~IComponent()
	{
	}

	virtual TypeId RealType() = 0;
    virtual bool IsType(TypeId iid) = 0;
};

class IMovable
{
public:
};

typedef IComponent* ComponentRef;

C3_NAMESPACE_END

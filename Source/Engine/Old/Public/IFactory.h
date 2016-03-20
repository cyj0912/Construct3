#pragma once
#include <Core.h>
#include <TypeId.h>

C3_NAMESPACE_BEGIN

class IFactory
{
protected:
	~IFactory()
	{
	}

public:
	virtual bool NewComponent(TypeId iid, void** outPtr) = 0;
};

C3_NAMESPACE_END

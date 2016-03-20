#include "Component.h"
C3_NAMESPACE_BEGIN

CBaseComponent::CBaseComponent()
{
	RefCount = 0;
}

void CBaseComponent::AddRef()
{
	RefCount++;
}

void CBaseComponent::Release()
{
	auto count = RefCount--;
	if (count == 0)
		delete this;
}

TypeId CBaseComponent::RealType()
{
	return GetTypeId<IComponent>();
}

bool CBaseComponent::IsType(TypeId id)
{
	if (id == GetTypeId<IComponent>())
		return true;
	return false;
}

bool CBaseComponent::QueryInterface(TypeId iid, void **outPtr)
{
	bool success = false;
	if (iid == GetTypeId<IComponent>())
	{
		success = true;
		*outPtr = static_cast<IComponent*>(this);
	}
	return success;
}

CMovable::CMovable()
{
}

CMovable::~CMovable()
{
}

C3_NAMESPACE_END

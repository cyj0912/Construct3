#include "Resource.h"
C3_NAMESPACE_BEGIN
RResource::~RResource()
{
}

RResource::RResource()
    : RefCount(0), Parent(nullptr)
{
    AddRef();
}

void RResource::AddRef()
{
    RefCount++;
}

void RResource::Release()
{
    auto a = RefCount--;
	if (a == 0)
	{
		delete this;
		Parent->Release();
	}
}

RResource* RResource::GetParent() const
{
	Parent->AddRef();
    return Parent;
}

void RResource::SetParent(RResource *parent)
{
	if (Parent)
		Parent->Release();
    Parent = parent;
	Parent->AddRef();
}
C3_NAMESPACE_END

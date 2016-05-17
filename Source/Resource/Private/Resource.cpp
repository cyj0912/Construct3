#include "Resource.h"
C3_NAMESPACE_BEGIN
RResource::~RResource()
{
	if (Parent)
		Parent->Release();
}

RResource::RResource()
    : Parent(nullptr)
{
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

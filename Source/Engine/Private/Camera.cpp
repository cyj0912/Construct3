#include "Camera.h"
#include "Component.h"
C3_NAMESPACE_BEGIN
C3_DEFINE_ENTITY(ECamera)

void ECamera::Spawn(FEntityRef parent)
{
    EActor::Spawn(parent);
}

void ECamera::Update()
{
	EActor::Update();
}

void ECamera::Kill()
{
	EActor::Kill();
}

C3_NAMESPACE_END

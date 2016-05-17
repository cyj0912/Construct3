#include "Camera.h"
C3_NAMESPACE_BEGIN
C3_DEFINE_ENTITY(ACamera)

void ACamera::Spawn(FEntityRef parent)
{
	AActor::Spawn(parent);
}

void ACamera::Update()
{
	AActor::Update();
}

void ACamera::Kill()
{
	AActor::Kill();
}

C3_NAMESPACE_END

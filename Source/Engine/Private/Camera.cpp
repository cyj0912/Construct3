#include "Camera.h"
#include "Component.h"
C3_NAMESPACE_BEGIN

C3_DEFINE_ENTITY(ECamera)

ECamera::ECamera()
{

}

void ECamera::Spawn(FEntityRef parent)
{
    CTransform* transform = new CTransform;
    this->AddChild(transform);
    this->AttachComponent(transform);
    EEntity::Spawn(parent);
}

void ECamera::Kill()
{
    EEntity::Kill();
    CTransform* transform = static_cast<CTransform*>(this->GetComponent(GetTypeId<CTransform>()));
    delete transform;
}

C3_NAMESPACE_END

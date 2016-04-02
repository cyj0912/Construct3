#include "Camera.h"
#include "Component.h"
C3_NAMESPACE_BEGIN

ECamera::ECamera()
{

}

void ECamera::Spawn(FEntityRef parent)
{
    EEntity::Spawn(parent);
    CTransform* transform = new CTransform;
    ChildEntities.push_back(transform);
    AttachComponent(transform);
}

C3_NAMESPACE_END

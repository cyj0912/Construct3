#pragma once
#include <Core.h>
#include "Actor.h"
C3_NAMESPACE_BEGIN
class ACamera : public AActor
{
	C3_DECLARE_ENTITY(ACamera)
public:
    virtual void Spawn(FEntityRef parent) override;
	virtual void Update() override;
    virtual void Kill() override;
};
C3_NAMESPACE_END

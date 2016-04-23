#pragma once
#include <Core.h>
#include "Actor.h"
C3_NAMESPACE_BEGIN
class ECamera : public EActor
{
public:
    virtual void Spawn(FEntityRef parent) override;
	virtual void Update() override;
    virtual void Kill() override;
};
C3_NAMESPACE_END

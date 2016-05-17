#pragma once
#include "Entity.h"

C3_NAMESPACE_BEGIN

class EScene : public EEntity
{
	C3_DECLARE_ENTITY(EScene)
public:
    EScene();
    ~EScene();
    virtual void Spawn(FEntityRef parent) override;
    virtual void Update() override;
	static void PrintSceneInfo(FEntityRef node, std::string indent, bool last);
};

C3_NAMESPACE_END

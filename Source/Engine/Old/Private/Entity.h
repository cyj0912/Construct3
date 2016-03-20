#pragma once
#include <Core.h>
#include <IEntity.h>
#include <IComponent.h>
#include <vector>

C3_NAMESPACE_BEGIN

class EEntity : public IEntity
{
public:
    EEntity();
    bool HasComponent(TypeId iid) override;
    bool QueryComponent(TypeId iid, void** outPtr) override;
    bool RegisterComponent(IComponent* pCom) override;
    bool DisableComponent(TypeId iid) override;
    bool EnableComponent(TypeId iid) override;
    bool RemoveComponent(TypeId iid) override;

private:
    std::vector<ComponentRef> Components;
};

C3_NAMESPACE_END

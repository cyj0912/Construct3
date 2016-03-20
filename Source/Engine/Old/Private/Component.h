#pragma once
#include <Core.h>
#include <IEntity.h>
#include <IComponent.h>
#include <glm/glm.hpp>

C3_NAMESPACE_BEGIN

class CBaseComponent : public IComponent
{
public:
    CBaseComponent();
    virtual ~CBaseComponent() {}
    void AddRef() override;
    void Release() override;
    bool QueryInterface(TypeId iid, void **outPtr) override;
    TypeId RealType() override;
    bool IsType(TypeId iid) override;

private:
    unsigned int RefCount;
	EntityRef ParentEntity;
};

template <typename T, typename P, typename TI>
class TInheritCom : public P, public TI
{
public:
    virtual bool QueryInterface(TypeId iid, void **outPtr) override
    {
        if(iid == GetTypeId<TI>())
        {
            *outPtr = this;
            return true;
        }
        return P::QueryInterface(iid, outPtr);
    }

    virtual TypeId RealType() override
    {
        return GetTypeId<TI>();
    }

    virtual bool IsType(TypeId iid) override
    {
        if(iid == GetTypeId<TI>())
        {
            return true;
        }
        return P::IsType(iid);
    }
};

class CMovable : public TInheritCom<CMovable, CBaseComponent, IMovable>
{
public:
    CMovable();
	~CMovable() override;

protected:
    glm::vec3 Position;
    glm::vec3 Scale;
    glm::vec4 Rotation;
};

C3_NAMESPACE_END

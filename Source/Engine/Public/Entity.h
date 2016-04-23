#pragma once
#include <Core.h>
#include "TypeId.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>

C3_NAMESPACE_BEGIN

class EEntity;

class FEntityRef
{
public:
    FEntityRef() : Pointer(nullptr) {}
    FEntityRef(EEntity* p) : Pointer(p) {}
	bool operator==(const FEntityRef& rhs) const
	{
		return Pointer == rhs.Pointer;
	}

	bool operator==(void* rhs) const
	{
		return Pointer == rhs;
	}

    EEntity* operator->() const
    {
        return Pointer;
    }

    EEntity& operator*() const
    {
        return *Pointer;
    }
private:
    EEntity* Pointer;
};
C3_NAMESPACE_END

namespace std
{
	template <> class hash<c3::FEntityRef>
	{
	public:
		size_t operator()(const c3::FEntityRef& ref) const
		{
			return hash<c3::EEntity*>()(ref.operator->());
		}
	};
}

C3_NAMESPACE_BEGIN
template <class T>
class FNode
{
public:
    using FChildren = std::unordered_set<T>;
    T GetParent()
    {
        return ParentEntity;
    }

    void SetParent(T parent)
    {
        ParentEntity = parent;
    }

    typename FChildren::iterator GetBeginChild()
    {
        return ChildEntities.begin();
    }

    typename FChildren::iterator GetEndChild()
    {
        return ChildEntities.end();
    }

    void AddChild(T child)
    {
        ChildEntities.insert(child);
    }

    void RemoveChild(T child)
    {
        ChildEntities.erase(child);
    }
private:
    T ParentEntity;
    FChildren ChildEntities;
};

class FCompContainer
{
public:
    void AttachComponent(FEntityRef ref);
    FEntityRef GetComponent(TypeId typeId);
	template <typename T> T* GetComponent(TypeId typeId)
	{
		if (Components.find(typeId) != Components.end())
			return static_cast<T*>(Components[typeId].operator->());
		return nullptr;
	}
    void DetachComponent(TypeId typeId);
    void PrintCompInfo();

private:
    std::unordered_map<TypeId, FEntityRef> Components;
};

class EEntity : public FNode<FEntityRef>
{
public:
    EEntity();
    virtual ~EEntity();
    virtual void Spawn(FEntityRef parent = nullptr);
    virtual void Update();
    virtual void Kill();
	virtual bool ShouldRelease();
};

C3_NAMESPACE_END

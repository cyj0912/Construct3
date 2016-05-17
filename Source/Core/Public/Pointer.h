
// TODO:
// Be very careful with this file
#pragma once
#include <Namespace.h>
C3_NAMESPACE_BEGIN
class FRefCount
{
    int RefCount;
protected:
    FRefCount();
    virtual ~FRefCount();
public:
    void AddRef();
    void Release();
};

template <typename T>
class FAutoRefPtr
{
    T* Pointer;
public:
    FAutoRefPtr() : Pointer(nullptr) {}
    FAutoRefPtr(T* assign) : Pointer(assign) {}

    FAutoRefPtr(const FAutoRefPtr& from)
    {
        Pointer = from.Pointer;
        Pointer->AddRef();
    }
    FAutoRefPtr & operator=(T* assign)
    {
        Clear();
        Pointer = assign;
        Pointer->AddRef();
        return *this;
    }
    FAutoRefPtr & operator=(const FAutoRefPtr& another)
    {
        Clear();
        Pointer = another.Pointer;
        Pointer->AddRef();
        return *this;
    }
    ~FAutoRefPtr()
    {
        Clear();
    }

    void Clear()
    {
        if(Pointer)
            Pointer->Release();
        Pointer = nullptr;
    }

    T& operator*() const
    {
        return *Pointer;
    }

    T* operator->() const
    {
        return Pointer;
    }

    operator T*() const
    {
        return Pointer;
    }
};
C3_NAMESPACE_END

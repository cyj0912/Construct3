
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

/*
 * Reference counting rules:
 *   1. Constructors automatically increments refcount, you must bind rvalue pointers to a lvalue.
 *   2. lvalue pointers take ownership, Release() it before going out of scope.
 *
 *   FAutoRefPtr steals ownership from rvalue pointers, shares ownership with lvalue pointers
 */

template <typename T>
class FAutoRefPtr
{
    T* Pointer;
public:
    //Default constructor
    FAutoRefPtr() : Pointer(nullptr) {}

    FAutoRefPtr(const FAutoRefPtr& from)
    {
        Pointer = from.Pointer;
        Pointer->AddRef();
    }
    FAutoRefPtr(FAutoRefPtr&& from)
    {
        Pointer = from.Pointer;
        from.Pointer = nullptr;
    }
    FAutoRefPtr & operator=(const FAutoRefPtr& from)
    {
        Clear();
        Pointer = from.Pointer;
        Pointer->AddRef();
        return *this;
    }
    FAutoRefPtr & operator=(FAutoRefPtr&& from)
    {
        Clear();
        Pointer = from.Pointer;
        from.Pointer = nullptr;
        return *this;
    }

    FAutoRefPtr(T* & from) : Pointer(from)
    {
        Pointer->AddRef();
    }
    FAutoRefPtr(T* && from) : Pointer(from) {}
    FAutoRefPtr & operator=(T* & from)
    {
        Clear();
        Pointer = from;
        Pointer->AddRef();
        return *this;
    }
    FAutoRefPtr & operator=(T* && from)
    {
        Clear();
        Pointer = from;
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

    explicit operator bool() const
    {
        return Pointer != nullptr;
    }

    explicit operator T*() const
    {
        return Pointer;
    }
};
C3_NAMESPACE_END

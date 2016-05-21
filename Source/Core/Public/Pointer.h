
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
 *   FAutoRef steals ownership from rvalue pointers, shares ownership with lvalue pointers
 */

template <typename T>
class FAutoRef
{
    T* Pointer;
public:
    //Default constructor
    FAutoRef() : Pointer(nullptr) {}

    FAutoRef(const FAutoRef& from)
    {
        Pointer = from.Pointer;
        Pointer->AddRef();
    }
    FAutoRef(FAutoRef&& from)
    {
        Pointer = from.Pointer;
        from.Pointer = nullptr;
    }
    FAutoRef & operator=(const FAutoRef& from)
    {
        Clear();
        Pointer = from.Pointer;
        Pointer->AddRef();
        return *this;
    }
    FAutoRef & operator=(FAutoRef&& from)
    {
        Clear();
        Pointer = from.Pointer;
        from.Pointer = nullptr;
        return *this;
    }

    FAutoRef(T* & from) : Pointer(from)
    {
        Pointer->AddRef();
    }
    FAutoRef(T* && from) : Pointer(from) {}
    FAutoRef & operator=(T* & from)
    {
        Clear();
        Pointer = from;
        Pointer->AddRef();
        return *this;
    }
    FAutoRef & operator=(T* && from)
    {
        Clear();
        Pointer = from;
        return *this;
    }

    ~FAutoRef()
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

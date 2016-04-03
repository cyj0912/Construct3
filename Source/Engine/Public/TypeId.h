#pragma once
#include <typeinfo>

namespace c3
{

using TypeId = std::size_t;

template <typename T>
TypeId GetTypeId()
{
    return typeid(T).hash_code();
}

template <typename T>
void* GetNewInstance();

}

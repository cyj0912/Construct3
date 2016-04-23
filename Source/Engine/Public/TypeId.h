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

#define C3_DEFINE_ENTITY(name) \
template<> void* GetNewInstance<name>() { return new name; } \
struct FEntityInfo##name \
{ \
	FEntityInfo##name() \
	{ \
		Data.Next = EntityInfoList; \
		EntityInfoList = &Data; \
		Data.ThisClass = GetTypeId<name>(); \
		Data.Factory = &GetNewInstance<name>; \
	} \
	FEntityInfo Data; \
} EntityInfo##name;

struct FEntityInfo
{
	FEntityInfo* Next;
	TypeId ThisClass;
	void*(*Factory)(void);
};
extern FEntityInfo* EntityInfoList;

}

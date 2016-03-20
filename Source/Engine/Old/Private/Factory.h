#pragma once
#include <Core.h>
#include <IFactory.h>
#include <unordered_map>
#include <functional>

C3_NAMESPACE_BEGIN

template <typename IT, typename T>
class TGenericFactory
{
public:
	IT* operator()()
	{
		return new T;
	}
};

class FFactory : public IFactory
{
public:
    bool NewComponent(TypeId iid, void** outPtr) override;

    template <typename IT, typename T>
    void RegisterComponent()
    {
		ComFactoryMap[GetTypeId<IT>()] = TGenericFactory<IT, T>();
    }

private:
	static std::unordered_map<TypeId, std::function<void*()>> ComFactoryMap;
};

C3_NAMESPACE_END

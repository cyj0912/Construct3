/*
Here is a list of all entity classes so that people don't get lost:

Cursor
Entity
InvisibleWall
PathPen
Player
Scene

List of all components can be found in ComponentId.hpp

All components are to be inherited by an entity, therefore "this" pointer
shall be able to access both the component and the entity. GetComponent()
is used to test the availbility of certain component of an entity.

*/

#pragma once
#include <functional>
#include <string>
#include "Serializable.hpp"

namespace mf {
unsigned long long GetTimeCounterMS();

class Entity : public Serializable
{
public:
	void Serialize(ObjectWrtier& obj) override
	{
		obj.SetProperty("EntityName", EntityName);
	}

	void Deserialize(ObjectReader& obj) override
	{
		EntityName = obj.GetProperty("EntityName");
	}

	Entity()
	{
		ThinkEnabled = false;
	}

	virtual ~Entity()
	{
	}

	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	virtual void Reset()
	{
		ThinkEnabled = false;
	}

	virtual void Tick()
	{
		if (ThinkEnabled)
		{
			if (NextThinkTick == 0)
				ThinkFunc(this);
			else
				while (1)
				{
					if (NextThinkTick < GetTimeCounterMS())
						ThinkFunc(this);
					else
						break;
				}
		}
	}

	void SetThinkFunc(void (Entity::*ptr)()) {
		if (ptr == nullptr)
			ThinkEnabled = false;
		ThinkFunc = std::mem_fn(ptr);
	}

	void SetNextThink(int deltaTick) {
		if (deltaTick < 0)
			ThinkEnabled = false;
		if (deltaTick == 0)
			NextThinkTick = 0;
		NextThinkTick = GetTimeCounterMS() + deltaTick;
	}

	virtual void GetComponent(int cid, void** returnPtr)
	{
		*returnPtr = nullptr;
	}

	std::string& GetName()
	{
		return EntityName;
	}
	
	void SetName(const std::string& n)
	{
		EntityName = n;
	}

private:
	std::function<void(Entity*)> ThinkFunc;
	bool ThinkEnabled;
	int NextThinkTick;
	std::string EntityName;
};

}

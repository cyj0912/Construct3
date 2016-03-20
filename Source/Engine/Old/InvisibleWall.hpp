//This is the thing that level designers are going to draw

#pragma once
#include "Collidable.hpp"
#include "ComponentId.hpp"
#include "Entity.hpp"
#include "Movable.hpp"

namespace mf {

class InvisibleWall : public Entity, public Movable, public Collidable {
public:
	void Serialize(ObjectWrtier& obj) override
	{
		Entity::Serialize(obj);
		obj.SetClass("InvisibleWall");
		Movable::Serialize(obj);
		Collidable::Serialize(obj);
	}

	void Deserialize(ObjectReader& obj) override
	{
		Entity::Deserialize(obj);
		Movable::Deserialize(obj);
		Collidable::Deserialize(obj);
		InitPhysicsBody();
	}

	~InvisibleWall() override
	{
	}

	void Tick() override
	{
		Entity::Tick();
		Collidable::Update();
	}

	void GetComponent(int cid, void** returnPtr) override
	{
		Entity::GetComponent(cid, returnPtr);
		if (*returnPtr != nullptr)
			return;
		if (cid == MF_MOVABLE)
			*returnPtr = static_cast<Movable*>(this);
		if (cid == MF_COLLIDABLE)
			*returnPtr = static_cast<Collidable*>(this);
	}
};

}

#pragma once
#include "Collidable.hpp"
#include "ComponentId.hpp"
#include "Drawable.hpp"
#include "Entity.hpp"
#include "Movable.hpp"
#include "Scene.hpp"

namespace mf {

class Player : public Entity, public Movable, public Drawable, public Collidable, public InputEventListener {
public:
	void OnEvent(int e) override
	{
		switch(e)
		{
		case W_DOWN:
			DirVector += glm::vec2(0.0f, 1.0f);
			break;
		case A_DOWN:
			DirVector += glm::vec2(-1.0f, 0.0f);
			break;
		case S_DOWN:
			DirVector += glm::vec2(0.0f, -1.0f);
			break;
		case D_DOWN:
			DirVector += glm::vec2(1.0f, 0.0f);
			break;
		case W_UP:
			DirVector -= glm::vec2(0.0f, 1.0f);
			break;
		case A_UP:
			DirVector -= glm::vec2(-1.0f, 0.0f);
			break;
		case S_UP:
			DirVector -= glm::vec2(0.0f, -1.0f);
			break;
		case D_UP:
			DirVector -= glm::vec2(1.0f, 0.0f);
			break;
		default:
			break;
		}
	}

	void Serialize(ObjectWrtier& obj) override
	{
		Entity::Serialize(obj);
		obj.SetClass("Player");
		Movable::Serialize(obj);
		Collidable::Serialize(obj);
	}

	void Deserialize(ObjectReader& obj) override
	{
		Entity::Deserialize(obj);
		Movable::Deserialize(obj);
		Collidable::Deserialize(obj);
	}

	void GetComponent(int cid, void** returnPtr) override
	{
		Entity::GetComponent(cid, returnPtr);
		if (*returnPtr != nullptr)
			return;
		if (cid == MF_MOVABLE)
			*returnPtr = static_cast<Movable*>(this);
		if (cid == MF_DRAWABLE)
			*returnPtr = static_cast<Drawable*>(this);
		if (cid == MF_COLLIDABLE)
			*returnPtr = static_cast<Collidable*>(this);
	}

	Player()
	{
		AtScene = nullptr;
		SetName("Player");
		ShapeType = "Player";
		InitPhysicsBody();
		GlobalInputHandler.Listeners.push_back(this);
	}

	~Player() override
	{
		GlobalInputHandler.EraseFromListener(this);
	}

	void Tick() override
	{
		Entity::Tick();
		Collidable::Update();
		PhyObject->MoveForward(DirVector);
		Drawable::AddToDrawList();
	}

	Scene* AtScene;
	glm::vec2 DirVector;
};

}

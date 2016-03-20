#pragma once
#include "Box2DIntegration.hpp"
#include "ComponentId.hpp"
#include "Movable.hpp"
#include "Serializable.hpp"

namespace mf {

class Collidable : public Serializable {
public:
	Collidable()
	{
		PhyObject = nullptr;
	}

	~Collidable()
	{
		if (PhyObject)
			delete PhyObject;
	}

	virtual void GetComponent(int cid, void** returnPtr) = 0;
	void Serialize(ObjectWrtier& obj) override
	{
		obj.SetProperty("ShapeType", ShapeType);
		if (ShapeType == "EdgeChain")
			ChainDef = EdgePainter.ToString();
		obj.SetProperty("ChainDef", ChainDef);
	}

	void Deserialize(ObjectReader& obj) override
	{
		ShapeType = obj.GetProperty("ShapeType");
		ChainDef = obj.GetProperty("ChainDef");
	}

	void InitPhysicsBody()
	{
		if (ShapeType == "EdgeChain")
		{
			EdgePainter.FromString(ChainDef);
			PhyObject = new PhysicsObject(EdgePainter);
		}
		else if (ShapeType == "Player")
		{
			PhyObject = new PhysicsObject(1);
		}
	}

	void Update()
	{
		Movable* mov = nullptr;
		GetComponent(MF_MOVABLE, (void**)&mov);
		if (mov != nullptr)
		{
			//Update Position etc. to Movable
			mov->Position = PhyObject->GetPosition();
			mov->Rotation = PhyObject->GetRotation();
		}
	}

	std::string ShapeType, ChainDef;
	PhysicsObject* PhyObject;
	WallEdgePainter EdgePainter;
};

}

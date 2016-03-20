#pragma once
#include <glm/glm.hpp>
#include "Serializable.hpp"

namespace mf {

class Movable : public Serializable {
public:
	virtual void GetComponent(int cid, void** returnPtr) = 0;

	void Serialize(ObjectWrtier& obj) override
	{
		obj.SetProperty("Position", to_string(Position));
		obj.SetProperty("Scale", to_string(Scale));
		obj.SetProperty("Rotation", std::to_string(Rotation));
	}

	void Deserialize(ObjectReader& obj) override
	{
		Position = stovec2(obj.GetProperty("Position"));
		Scale = stovec2(obj.GetProperty("Scale"));
		Rotation = std::stof(obj.GetProperty("Rotation"));
	}

	void Update()
	{
	}

	glm::vec2 Position;
	glm::vec2 Scale;
	float Rotation;
};

}

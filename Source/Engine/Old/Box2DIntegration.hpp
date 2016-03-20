#pragma once
#include <Box2D/Box2D.h>
#include <sstream>
#include <vector>
#include <glm/gtx/norm.hpp>

namespace mf {

struct PhysicsContext
{
	b2World* World;
} *GPhysicsContext;

class PhysicsScene {
public:
	explicit PhysicsScene()
		: World(nullptr)
	{
		b2Vec2 gravity(0.0f, 0.0f);
		World = new b2World(gravity);
		Context.World = World;
	}

	~PhysicsScene()
	{
		delete World;
	}

	void SetAsCurrentContext()
	{
		GPhysicsContext = &Context;
	}

	void Tick()
	{
		World->Step(30.0f / 1000.0f, 12, 4);
	}

	PhysicsContext Context;
	b2World* World;
};

class WallEdgePainter {
public:
	std::vector<float> Points;
	b2ChainShape Shape;
	void AppendPoint(float a, float b)
	{
		Points.push_back(a);
		Points.push_back(b);
	}
	void DeletePoint()
	{
		Points.erase(Points.end() - 1);
		Points.erase(Points.end() - 1);
	}
	b2ChainShape GenerateShape()
	{
		int NumberPts = Points.size() / 2;
		b2Vec2* PointVec = new b2Vec2[NumberPts];
		for (int i = 0; i < NumberPts; i++)
			PointVec[i].Set(Points[2 * i], Points[2 * i + 1]);
		Shape.CreateChain(PointVec, NumberPts);
		return Shape;
	}
	void ReleaseShape(b2Shape* s)
	{
		delete s;
	}
	std::string ToString()
	{
		std::stringstream ss;
		for (auto value : Points)
			ss << value << " ";
		return ss.str();
	}
	void FromString(const std::string& str)
	{
		std::stringstream ss(str);
		std::string s;
		while (ss >> s)
			Points.push_back(std::stof(s));
	}
};

class PhysicsObject {
public:
	PhysicsObject()
	{
		Body = nullptr;
	}
	PhysicsObject(int predefined)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(0.0f, 0.0f);
		Body = GPhysicsContext->World->CreateBody(&bodyDef);

		b2PolygonShape box;
		box.SetAsBox(0.5f, 0.5f);

		b2FixtureDef fixDef;
		fixDef.shape = &box;
		fixDef.density = 1.0f;
		fixDef.friction = 0.3f;
		Body->CreateFixture(&fixDef);
	}
	PhysicsObject(b2Shape& shape)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position.Set(0.0f, 0.0f);
		Body = GPhysicsContext->World->CreateBody(&bodyDef);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		Body->CreateFixture(&fixtureDef);
	}
	PhysicsObject(WallEdgePainter& painter)
	{
		b2ChainShape s = painter.GenerateShape();
		
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position.Set(0.0f, 0.0f);
		Body = GPhysicsContext->World->CreateBody(&bodyDef);

		Body->CreateFixture(&painter.Shape, 0.0f);
	}
	~PhysicsObject()
	{
		if (Body)
			GPhysicsContext->World->DestroyBody(Body);
	}

	glm::vec2 GetPosition()
	{
		b2Vec2 v = Body->GetPosition();
		return glm::vec2(v.x, v.y);
	}

	float GetRotation()
	{
		return Body->GetAngle();
	}

	void MoveForward(glm::vec2 dir)
	{
		if (glm::length(dir) < 0.5f)
		{
			GPhysicsContext->World->ClearForces();
			return;
		}
		dir = glm::normalize(dir);
		dir *= 10.0f;
		Body->ApplyForceToCenter(b2Vec2(dir.x, dir.y), true);
	}

	b2Body* Body;
};

}

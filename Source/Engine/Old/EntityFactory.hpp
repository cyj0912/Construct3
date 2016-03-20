#pragma once
#include "InvisibleWall.hpp"
#include "PathPen.hpp"
#include "Player.hpp"
#include "Scene.hpp"

namespace mf
{
	class Entity;

	class EntityFactory {
	public:
		static EntityFactory& getSingleton() { return singleton; }
		Entity* createEntity(const char* className) {
			std::string Name(className);
			if (Name == "Scene")
				return new Scene();
			else if (Name == "Player")
				return new Player();
			else if (Name == "InvisibleWall")
				return new InvisibleWall();
			else if (Name == "PathPen")
				return new PathPen();
			return nullptr;
		}
	private:
		EntityFactory()
		{
		}
		static EntityFactory singleton;
	};

	EntityFactory EntityFactory::singleton;

	Entity* CreateEntity(const char* className)
	{
		return EntityFactory::getSingleton().createEntity(className);
	}
}

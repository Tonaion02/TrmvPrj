#pragma once

#include <array>
#include <vector>

#include "ECS/Entity.h"





class EntityManager
{
public:
	static EntityManager& get()
	{
		static EntityManager instance;
		return instance;
	}

	Entity createEntity();
	void deleteEntity(const Entity& entityToDelete);

	//Friend function
	friend void debugInfoEntity();

protected:
	EntityManager()
		:mNextId(1)
	{
	}

protected:

	std::array<Entity, MAX_ENTITIES> mEntities;
	std::vector<Entity> mDeadEntities;

	unsigned int mNextId;
};
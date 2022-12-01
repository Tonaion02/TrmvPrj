#pragma once

#include <array>
#include <vector>

#include "ECS/Entity.h"
#include "ECS/Signature.h"





class EntityManager
{
public:
	static EntityManager& get()
	{
		static EntityManager instance;
		return instance;
	}

	Entity createEntity();
	void deleteEntity(Entity entityToDelete);
	bool isThereTypeCmp(Entity e, unsigned int typeCmp);
	bool isThisType(Entity e, Signature typeEntity);
	void registerTypeSignature(Entity e, unsigned int typeCmp);
	void unRegisterTypeSignature(Entity e, unsigned int typeCmp);

protected:
	EntityManager()
		:mNextId(0)
	{
	}

protected:
	std::array<Entity, MAX_ENTITIES> mEntities;
	std::vector<Entity> mDeadEntities;

	std::array<Signature, MAX_ENTITIES> typeSignatures;

	unsigned int mNextId;
};
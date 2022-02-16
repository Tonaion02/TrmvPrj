#include "ECS/EntityManager.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class EntityManager
//-----------------------------------------------------------------------------------------------------------------------------------------
Entity EntityManager::createEntity()
{
	if (!mDeadEntities.empty())
	{
		Entity e = mDeadEntities.back();
		mDeadEntities.pop_back();
		return e;
	}

	Entity e;
	e = mNextId++;

	///ADD ASSERT ON MUX NUMBER OF ENTITIES
	return e;
}



void EntityManager::deleteEntity(const Entity& entityToDelete)
{
	mDeadEntities.push_back(entityToDelete);
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class EntityManager
//-----------------------------------------------------------------------------------------------------------------------------------------
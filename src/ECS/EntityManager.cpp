#include "ECS/EntityManager.h"

#include "utils/PersonalAssert.h"

#include "ECS/ComponentPool.h"

#include "ECS/DataManager.h"





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

	Entity e = mNextId++;

	///ADD ASSERT ON MAX NUMBER OF ENTITIES
	ASSERT(((unsigned int)e < MAX_ENTITIES));

	return e;
}



void EntityManager::deleteEntity(Entity entityToDelete)
{
	mDeadEntities.push_back(entityToDelete);

	for (unsigned int i = 0; i < MAX_TYPE_CMPS; i++)
		if(signatures[entityToDelete][i])
			(*DataManager::get().getPools())[i]->unRegisterEntity(entityToDelete);

	signatures[entityToDelete].reset();
}



bool EntityManager::isThereTypeCmp(Entity e, unsigned int typeCmp)
{
	return signatures[e][typeCmp];
}



void EntityManager::registerSignature(Entity e, unsigned int typeCmp)
{
	signatures[e][typeCmp] = 1;
}



void EntityManager::unRegisterSignature(Entity e, unsigned int typeCmp)
{
	signatures[e][typeCmp] = 0;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class EntityManager
//-----------------------------------------------------------------------------------------------------------------------------------------
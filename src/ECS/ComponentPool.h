#pragma once

#include "ECS/TypeManager.h"
#include "ECS/SignatureManager.h"

#include "ECS/Entity.h"

#include "SDL_Enviroment.h"

#include <array>





template<typename TypeCmp>
struct ComponentPool
{
	std::array<Entity, MAX_ENTITIES> mDirectArray;
	std::array<unsigned int, MAX_ENTITIES> mReverseArray;
	std::array<TypeCmp, MAX_ENTITIES> mPackedArray;
	unsigned int mNext = 0;
};



template<typename TypeCmp>
TypeCmp* getCmpEntity(ComponentPool<TypeCmp>* pool, Entity e)
{
	return &pool->mPackedArray[pool->mReverseArray[e]];
}



template<typename TypeCmp>
void registerEntity(ComponentPool<TypeCmp>* pool, Entity e)
{
	pool->mReverseArray[e] = pool->mNext;
	pool->mDirectArray[pool->mNext] = e;

	pool->mNext++;

	//Unregister a type on the signature of the Entity
	SignatureManager::get().registerTypeCmp(e, (int)getIndexFromType<TypeCmp>() );
}



template<typename TypeCmp>
void unregisterEntity(ComponentPool<TypeCmp>* pool, Entity e)
{
	//Controll if we are unregistering under the limit
	if (pool->mNext == 1)
	{
		SDL_Log("!!!Unregistering under the limit!!!");
		return;
	}
	//Controll if we are unregistering under the limit

	//Controll if this entity is already unregistered
	if (pool->mReverseArray[e.id] == pool->mDirectArray.size())
	{
		SDL_Log("!!!Entity is already unregistered!!!");
		return;
	}
	//Controll if this entity is already unregistered

	unsigned int newId = pool->mDirectArray[pool->mNext - 1];

	pool->mDirectArray[pool->mReverseArray[e]] = pool->mDirectArray[pool->mNext - 1];
	pool->mPackedArray[pool->mReverseArray[e]] = pool->mPackedArray[pool->mNext - 1];

	pool->mDirectArray[pool->mReverseArray[newId]] = 0;

	pool->mReverseArray[newId] = pool->mReverseArray[e];

	pool->mNext--;

	pool->mReverseArray[e] = pool->mDirectArray.size();

	//Unregister a type from the signature of the Entity
	SignatureManager::get().unRegisterTypeCmp(e, getIndexFromType<TypeCmp>());
}
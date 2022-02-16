#pragma once

#include "ECS/Entity.h"

#include "SDL_Enviroment.h"

#include <array>





template<typename TypeComponent>
struct ComponentPool
{
	std::array<Entity, MAX_ENTITIES> mDirectArray;
	std::array<unsigned int, MAX_ENTITIES> mReverseArray;
	std::array<TypeComponent, MAX_ENTITIES> mPackedArray;
	unsigned int mNext=0;
};



template<typename TypeComponent>
void registerEntity(ComponentPool<TypeComponent>* pool, Entity e)
{
	pool->mReverseArray[e] = pool->mNext;
	pool->mDirectArray[pool->mNext] = e;

	pool->mNext++;
}



template<typename TypeComponent>
void unregisterEntity(ComponentPool<TypeComponent>* pool, Entity e)
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
}
#pragma once

#include "ECS/Limits.h"

#include "ECS/Entity.h"

#include "ECS/EntityManager.h"
#include "ECS/TypeManager.h"

#include "ECS/ComponentPool.h"

#include "ECS/DataManager.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//EntityManager interface
//-----------------------------------------------------------------------------------------------------------------------------------------
inline Entity createEntityId()
{
	return EntityManager::get().createEntity();
}

inline void deleteEntity(Entity e)
{
	EntityManager::get().deleteEntity(e);
}

template<typename TypeCmp>
bool isThereTypeCmp(Entity e)
{
	return EntityManager::get().isThereTypeCmp(e, idTypeCmp<TypeCmp>());
}

template<typename TypeCmp>
void registerSignature(Entity e)
{
	EntityManager::get().registerSignature(e, idTypeCmp<TypeCmp>());
}

template<typename TypeCmp>
void unRegisterSignature(Entity e)
{
	EntityManager::get().unRegisterSignature(e, idTypeCmp<TypeCmp>());
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//EntityManager interface
//-----------------------------------------------------------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------------------------------------------------------------
//ComponentPool interface
//-----------------------------------------------------------------------------------------------------------------------------------------
//template<typename TypeCmp>
//ComponentPool<TypeCmp>* getCmpPool();

template<typename TypeCmp>
TypeCmp* getCmpEntity(Entity e)
{
	ComponentPool<TypeCmp>* pool = (ComponentPool<TypeCmp>*)getCmpPool<TypeCmp>();
	return &pool->mPackedArray[pool->mReverseArray[e]];
}

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

	EntityManager::get().registerSignature(e, idTypeCmp<TypeCmp>());
}

template<typename TypeCmp>
void unRegisterEntity(ComponentPool<TypeCmp>* pool, Entity e)
{
	//Controll if this entity is already unregistered
	//if (pool->mReverseArray[e] == pool->mDirectArray.size())
	//{
	//	SDL_Log("!!!Entity is already unregistered!!!");
	//	return;
	//}
	//Controll if this entity is already unregistered

	Entity newId = pool->mDirectArray[pool->mNext - 1];

	pool->mDirectArray[pool->mReverseArray[e]] = pool->mDirectArray[pool->mNext - 1];
	pool->mPackedArray[pool->mReverseArray[e]] = pool->mPackedArray[pool->mNext - 1];

	//pool->mDirectArray[pool->mReverseArray[newId]] = 0;
	pool->mDirectArray[pool->mReverseArray[newId]] = MAX_ENTITIES;

	pool->mReverseArray[newId] = pool->mReverseArray[e];

	pool->mNext--;

	pool->mReverseArray[e] = (unsigned int)pool->mDirectArray.size();

	EntityManager::get().unRegisterSignature(e, idTypeCmp<TypeCmp>());
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//ComponentPool interface
//-----------------------------------------------------------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------------------------------------------------------------
//DataManager interface
//-----------------------------------------------------------------------------------------------------------------------------------------
template<typename TypeCmp>
ComponentPool<TypeCmp>* getCmpPool()
{
	return (ComponentPool<TypeCmp>*)DataManager::get().getPool(idTypeCmp<TypeCmp>());
}

inline std::array<struct BaseComponentPool*, MAX_TYPE_CMPS>* getCmpPools()
{
	return DataManager::get().getPools();
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//DataManager interface
//-----------------------------------------------------------------------------------------------------------------------------------------
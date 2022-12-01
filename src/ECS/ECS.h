#pragma once

#include "ECS/Limits.h"

#include "ECS/Entity.h"

#include "ECS/GroupEntity.h"

#include "ECS/EntityManager.h"

#include "ECS/TypeManager.h"
#include "ECS/TypeManagerComponents.h"
#include "ECS/TypeManagerScenes.h"

#include "ECS/ComponentPool.h"

#include "ECS/GroupEntity.h"

#include "ECS/Scene.h"
#include "ECS/SceneManager.h"

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

inline bool isThisTypeEntity(Entity e, Signature typeEntity)
{
	return EntityManager::get().isThisType(e, typeEntity);
}

template<typename TypeCmp>
void registerType(Entity e)
{
	EntityManager::get().registerSignature(e, idTypeCmp<TypeCmp>());
}

template<typename TypeCmp>
void unRegisterType(Entity e)
{
	EntityManager::get().unRegisterSignature(e, idTypeCmp<TypeCmp>());
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//EntityManager interface
//-----------------------------------------------------------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------------------------------------------------------------
//ComponentPool interface
//-----------------------------------------------------------------------------------------------------------------------------------------
template<typename TypeCmp>
TypeCmp& getCmpEntity(Entity e)
{
	ComponentPool<TypeCmp>& pool = getCmpPool<TypeCmp>();
	return pool.mPackedArray[pool.mReverseArray[e]];
}

template<typename TypeCmp>
TypeCmp& getCmpEntity(ComponentPool<TypeCmp>& pool, Entity e)
{
	return pool.mPackedArray[pool.mReverseArray[e]];
}

template<typename TypeCmp>
TypeCmp& getCmpIndex(ComponentPool<TypeCmp>& pool, unsigned int index)
{
	return pool.mPackedArray[index];
}

template<typename TypeCmp>
void registerEntity(ComponentPool<TypeCmp>& pool, Entity e)
{
	pool.mReverseArray[e] = pool.mNext;
	pool.mDirectArray[pool.mNext] = e;

	pool.mNext++;

	EntityManager::get().registerTypeSignature(e, idTypeCmp<TypeCmp>());
}

template<typename TypeCmp>
void unRegisterEntity(ComponentPool<TypeCmp>& pool, Entity e)
{
	ASSERT(pool->mReverseArray[e] != pool->mDirectArray.size());

	Entity newId = pool.mDirectArray[pool.mNext - 1];

	pool.mDirectArray[pool.mReverseArray[e]] = pool.mDirectArray[pool.mNext - 1];
	pool.mPackedArray[pool.mReverseArray[e]] = pool.mPackedArray[pool.mNext - 1];

	pool.mDirectArray[pool.mReverseArray[newId]] = pool->mDirectArray.size();

	pool.mReverseArray[newId] = pool.mReverseArray[e];

	pool.mNext--;

	pool.mReverseArray[e] = (unsigned int)pool.mDirectArray.size();

	EntityManager::get().unRegisterSignature(e, idTypeCmp<TypeCmp>());
}



//void registerE(Entity e, Signature sign) 
//{
//	Pools pools = DataManager::get().getPools();
//
//	for (int i=0;i<sign.size();i++)
//		if (sign.test(i))
//		{
//			pools.at(i)
//		}
//}
//-----------------------------------------------------------------------------------------------------------------------------------------
//ComponentPool interface
//-----------------------------------------------------------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------------------------------------------------------------
//GroupEntity interface
//-----------------------------------------------------------------------------------------------------------------------------------------
inline void registerEntity(GroupEntity<>& group, Entity e)
{
	//ASSERT: Controll if next is less than MAX_ENTITIES

	group.next++;
	group.reverseArray[e] = group.next;
	group.directArray[group.next] = e;
}

inline void unRegisterEntity(GroupEntity<>& group, Entity e)
{
	//ASSERT: Controll if next is not less than zero

	Entity entityToMove = group.directArray[group.next - 1];
	unsigned int pos = group.reverseArray[e];
	group.reverseArray[e] = MAX_ENTITIES;
	group.reverseArray[entityToMove] = pos;
	group.directArray[pos] = entityToMove;
	group.directArray[group.next - 1] = MAX_ENTITIES;
	group.next--;
}

inline bool isThereEntity(GroupEntity<>& group, Entity e)
{
	//ASSERT: 

	//return group->directArray[group->reverseArray[e]] != MAX_ENTITIES;
	return group.reverseArray[e] != MAX_ENTITIES;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//GroupEntity interface
//-----------------------------------------------------------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------------------------------------------------------------
//SceneManager interface
//-----------------------------------------------------------------------------------------------------------------------------------------
inline BaseScene* currentScene()
{
	return SceneManager::get().getCurrentScene();
}

inline void nextScene()
{
	SceneManager::get().nextScene();
}

inline void resetIteratorScene()
{
	SceneManager::get().resetIterator();
}

inline bool isEndedScenes()
{
	return SceneManager::get().isEndedScenes();
}

template<typename TypeScene>
BaseScene* getScene()
{
	return SceneManager::get().getScene(idTypeScenes<TypeScene>());
}

template<typename TypeScene>
bool isActiveScene()
{
	return SceneManager::get().isActive(idTypeScenes<TypeScene>());
}

template<typename TypeScene>
void addScene(class BaseScene* baseScene)
{
	SceneManager::get().addScene(idTypeScenes<TypeScene>(), baseScene);
}

template<typename TypeScene>
void activateScene()
{
	SceneManager::get().activateScene(idTypeScenes<TypeScene>());
}

template<typename TypeScene>
void deActivateScene()
{
	SceneManager::get().deActivateScene(idTypeScenes<TypeScene>());
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//SceneManager interface
//-----------------------------------------------------------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------------------------------------------------------------
//DataManager interface
//-----------------------------------------------------------------------------------------------------------------------------------------
template<typename TypeCmp>
ComponentPool<TypeCmp>& getCmpPool()
{
	return *(ComponentPool<TypeCmp>*)DataManager::get().getPool(idTypeCmp<TypeCmp>());
}

inline std::array<struct BaseComponentPool*, MAX_TYPE_CMPS>& getCmpPools()
{
	return DataManager::get().getPools();
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//DataManager interface
//-----------------------------------------------------------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------------------------------------------------------------
//TypeComponentManager interface
//-----------------------------------------------------------------------------------------------------------------------------------------
template<typename TypeCmp>
unsigned int idTypeCmp()
{
	return TypeManagerComponent::get().idType<TypeCmp>();
}

template<typename TypeCmp>
std::string stringTypeCmp()
{
	return TypeManagerComponent::get().stringType<TypeCmp>();
}

template<typename TypeCmp>
Signature getTypeSignature()
{
	return TypeManagerComponent::get().getTypeSignature<TypeCmp>();
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//TypeComponentManager interface
//-----------------------------------------------------------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------------------------------------------------------------
//TypeComponentManager interface
//-----------------------------------------------------------------------------------------------------------------------------------------
template<typename TypeScenes>
unsigned int idTypeScenes()
{
	return TypeManagerScenes::get().idType<TypeScenes>();
}

template<typename TypeScenes>
std::string stringTypeScenes()
{
	return TypeManagerScenes::get().stringType<TypeScenes>();
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//TypeComponentManager interface
//-----------------------------------------------------------------------------------------------------------------------------------------
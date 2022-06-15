#pragma once

#include <array>

#include "ECS/Entity.h"
#include "ECS/TypeManager.h"
#include "ECS/TypeManagerComponents.h"
#include "ECS/EntityManager.h"
#include "ECS/DataManager.h"





struct BaseComponentPool
{
	virtual void unRegisterEntity(Entity e) = 0;
};



template<typename TypeCmp>
struct ComponentPool : public BaseComponentPool
{
	std::array<Entity, MAX_ENTITIES> mDirectArray;
	std::array<unsigned int, MAX_ENTITIES> mReverseArray;
	std::array<TypeCmp, MAX_ENTITIES> mPackedArray;
	unsigned int mNext = 0;

	ComponentPool()
	{
		for (unsigned int i = 0; i < MAX_ENTITIES; i++)
			mDirectArray[i] = MAX_ENTITIES;

		for (unsigned int i = 0; i < MAX_ENTITIES; i++)
			mReverseArray[i] = MAX_ENTITIES;

		(*DataManager::get().getPools())[TypeManagerComponent::get().idTypeCmp<TypeCmp>()] = this;
	}

	void unRegisterEntity(Entity e)
	{
		Entity newId = this->mDirectArray[this->mNext - 1];

		this->mDirectArray[this->mReverseArray[e]] = this->mDirectArray[this->mNext - 1];
		this->mPackedArray[this->mReverseArray[e]] = this->mPackedArray[this->mNext - 1];

		//pool->mDirectArray[pool->mReverseArray[newId]] = 0;
		this->mDirectArray[this->mReverseArray[newId]] = MAX_ENTITIES;

		this->mReverseArray[newId] = this->mReverseArray[e];

		this->mNext--;

		this->mReverseArray[e] = (unsigned int)this->mDirectArray.size();

		//EntityManager::get().unRegisterSignature(e, idTypeCmp<TypeCmp>());
		EntityManager::get().unRegisterSignature(e, TypeManagerComponent::get().idTypeCmp<TypeCmp>());
	}
};
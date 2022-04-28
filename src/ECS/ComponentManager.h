#pragma once

#include "ECS/Entity.h"

#include <array>





template<typename TypeComponent>
class ComponentManager
{
public:
	static ComponentManager& get()
	{
		static ComponentManager instance;
		return instance;
	}

	void registerEntity(const Entity & e)
	{
		mReverseArray[e.id] = mLast;
		mDirectArray[mLast] = e;

		mLast++;
	}

	void unregisterEntity(const Entity & e)
	{
		//Controllare se si vuole cancellare oltre il limite consentito

		unsigned int newId = mDirectArray[mLast - 1];

		mDirectArray[mReverseArray[e.id]] = mDirectArray[mLast - 1];
		mPackedArray[mReverseArray[e.id]] = mPackedArray[mLast - 1];

		mDirectArray[mReverseArray[newId]].id = 0;

		mReverseArray[newId] = mReverseArray[e.id];

		mLast--;
	}

protected:
	ComponentManager() : mLast(0) {}

public:
	std::array<Entity, MAX_ENTITIES> mDirectArray;
	std::array<TypeComponent, MAX_ENTITIES> mPackedArray;
	std::array<unsigned int, MAX_ENTITIES> mReverseArray;
	unsigned int mLast;
};

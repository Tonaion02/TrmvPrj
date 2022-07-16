#pragma once

#include <array>

#include "Entity.h"





template<unsigned int SIZE = MAX_ENTITIES>
struct GroupEntity
{
	std::array<unsigned int, MAX_ENTITIES> reverseArray;
	std::array<Entity, SIZE> directArray;
	unsigned int next;

	GroupEntity()
		:next(0)
	{
		reverseArray.fill(MAX_ENTITIES);
		directArray.fill(MAX_ENTITIES);
	}

	void unRegisterEntity(Entity e)
	{
		//ASSERT: controll if next-1 is less than zero

		Entity entityToMove = directArray[next - 1];
		unsigned int pos = reverseArray[e];
		reverseArray[e] = MAX_ENTITIES;
		reverseArray[entityToMove] = pos;
		directArray[pos] = entityToMove;
		directArray[next - 1] = MAX_ENTITIES;
		next--;
	}
};
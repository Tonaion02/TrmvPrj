#pragma once

#include <stdio.h>

#include "ECS/Entity.h"
#include "ECS/ComponentManager.h"
#include "ECS/ComponentPool.h"
#include "SDL_Enviroment.h"





template<typename T>
void DebugInfoComponentManager(ComponentPool<T>* pool, unsigned int n)
{
	printf("Entity:\n|");
	for (unsigned int i = 0; i < n; i++)
	{
		printf("%d|", pool->mDirectArray[i].id);
	}

	printf("\n");
	printf("ReverseArray:\n|");
	for (unsigned int i = 0; i < n; i++)
	{
		printf("%d|", pool->mReverseArray[i]);
	}

	printf("\n");
	//printf("PackedArray:\n|");
	//for (int i = 0; i < n; i++)
	//{
	//	printf("")
	//}
}

void debugInfoEntity();
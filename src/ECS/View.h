#pragma once

#include <stdio.h>
#include <array>
#include <set>

#include "SDL_Enviroment.h"

#include "ECS/Limits.h"
#include "ECS/Signature.h"
#include "ECS/Entity.h"
#include "ECS/DataManager.h"
#include "ECS/TypeManager.h"




struct BaseView
{
	virtual void unRegisterEntity(Entity e) = 0;
};



template<typename T, typename... Types>
struct View : public BaseView
{
	//For Debug
	std::string debugNameScene;

	std::set<unsigned int> typeCmps;

	Signature signature;
	std::array<Entity, MAX_ENTITIES> directArray;
	std::array<unsigned int, MAX_ENTITIES> reverseArray;
	unsigned int next;

	View()
		:next(0), debugNameScene("")
	{
		for (unsigned int i = 0; i < MAX_ENTITIES; i++)
			directArray[i] = MAX_ENTITIES;

		for (unsigned int i = 0; i < MAX_ENTITIES; i++)
			reverseArray[i] = MAX_ENTITIES;

		//DataManager::get().getViews[] = 
		signature = createSignatureFromTypes<(T, Types)>();

		for (unsigned int i = 0; i < MAX_TYPE_CMPS; i++)
			if (signature[i])
				typeCmps.insert(i);
	}
};



//template<typename T>
//void registerType(Signature* v)
//{
//	(*v)[idTypeCmp<T>()] = 1;
//}
//
//
//
//template<typename... Ts>
//void registerTypes(Signature* v)
//{
//	(registerType<Ts>(v), ...);
//}
//
//
//
//template<typename... Ts>
// 
//{
//	static Signature signature;
//	static bool first = true;
//	if (first)
//	{
//		first = false;
//		registerTypes<Ts ...>(&signature);
//	}
//	return signature;
//}
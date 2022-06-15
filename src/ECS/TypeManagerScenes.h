#pragma once

#include "ECS/TypeManager.h"





class TypeManagerScenes : public TypeManager
{
public:
	static TypeManagerScenes& get()
	{
		static TypeManagerScenes instance;
		return instance;
	}
};
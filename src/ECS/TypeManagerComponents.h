#pragma once

#include "ECS/TypeManager.h"





class TypeManagerComponent : public TypeManager
{
public:
	static TypeManagerComponent& get()
	{
		static TypeManagerComponent instance;
		return instance;
	}
};
#pragma once

#include "ECS/TypeManager.h"

#include "ECS/Signature.h"





class TypeManagerComponent : public TypeManager
{
public:
	static TypeManagerComponent& get()
	{
		static TypeManagerComponent instance;
		return instance;
	}

	template<typename TypeCmp>
	Signature getTypeSignature()
	{
		Signature sign(0);
		sign[idType<TypeCmp>()] = 1;
		return sign;
	}
};
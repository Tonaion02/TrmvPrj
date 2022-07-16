#pragma once

#include <array>
#include <typeinfo>
#include <string>

#include "ECS/Limits.h"





class TypeManager
{
public:
	template<typename Type>
	unsigned int idType()
	{
		static const unsigned int id = nextId();
		return id;
	}

	template<typename Type>
	std::string stringType()
	{
		static std::string s = newString<Type>();
		return s;
	}

protected:
	TypeManager()
		:nextIDType(0)
	{}

	unsigned int nextId() { return nextIDType++; }
	
	template<typename Type>
	std::string newString()
	{
		stringTypes[idType<Type>()] = typeid(Type).name();
		return stringTypes[idType<Type>()];
	}

protected:
	unsigned int nextIDType;
	std::array<std::string, MAX_TYPE_CMPS> stringTypes;
};
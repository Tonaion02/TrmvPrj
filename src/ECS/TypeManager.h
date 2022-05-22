#pragma once

#include <array>
#include <typeinfo>
#include <string>

#include "ECS/Limits.h"





template<typename TypeCmp>
unsigned int idTypeCmp()
{
	return TypeManager::get().idTypeCmp<TypeCmp>();
}

template<typename TypeCmp>
std::string stringTypeCmp()
{
	return TypeManager::get().stringTypeCmp<TypeCmp>();
}



class TypeManager
{
public:
	static TypeManager& get()
	{
		static TypeManager instance;
		return instance;
	}

	template<typename TypeCmp>
	unsigned int idTypeCmp()
	{
		static const unsigned int id = TypeManager::get().nextId();
		return id;
	}

	template<typename TypeCmp>
	std::string stringTypeCmp()
	{
		static std::string s = TypeManager::get().newString<TypeCmp>();
		return s;
	}

protected:
	TypeManager()
		:nextIDTypeCmps(0)
	{}

	unsigned int nextId() { return nextIDTypeCmps++; }
	
	template<typename TypeCmp>
	std::string newString()
	{
		stringTypeCmps[idTypeCmp<TypeCmp>()] = typeid(TypeCmp).name();
		return stringTypeCmps[idTypeCmp<TypeCmp>()];
	}

protected:
	unsigned int nextIDTypeCmps;
	std::array<std::string, MAX_TYPE_CMPS> stringTypeCmps;
};
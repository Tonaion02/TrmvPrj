#pragma once

#include "ECS/Limits.h"





using Pools = std::array<struct BaseComponentPool*, MAX_TYPE_CMPS>;

class DataManager
{
public:
	static DataManager& get()
	{
		static DataManager instance;
		return instance;
	}

	inline std::array<struct BaseComponentPool*, MAX_TYPE_CMPS>& getPools() 
	{
		return pools; 
	}

	inline struct BaseComponentPool* getPool(unsigned int typeCmp)
	{
		return pools[typeCmp];
	}

protected:
	std::array<struct BaseComponentPool*, MAX_TYPE_CMPS> pools;
};
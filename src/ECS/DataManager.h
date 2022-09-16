#pragma once

#include "ECS/Limits.h"





class DataManager
{
public:
	static DataManager& get()
	{
		static DataManager instance;
		return instance;
	}

	inline std::array<struct BaseComponentPool*, MAX_TYPE_CMPS>* getPools() 
	{
		return &pools; 
	}

	inline struct BaseComponentPool* getPool(unsigned int typeCmp)
	{
		return pools[typeCmp];
	}

protected:
	//All the pools of Components
	std::array<struct BaseComponentPool*, MAX_TYPE_CMPS> pools;
};
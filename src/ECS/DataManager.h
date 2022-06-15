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

	inline std::array<struct BaseView*, MAX_VIEW>* getViews()
	{
		return &views;
	}

	inline struct BaseView* getView(unsigned int idView)
	{
		return views[idView];
	}

protected:
	//All the pools of Components
	std::array<struct BaseComponentPool*, MAX_TYPE_CMPS> pools;

	//All the view of Components
	std::array<struct BaseView*, MAX_VIEW> views;
};
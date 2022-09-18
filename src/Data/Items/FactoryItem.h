#pragma once

#include <unordered_map>
#include <string>
#include <functional>

#include "utils/StringAndFile/XMLvariab.h"





class FactoryItem
{
public:
	static FactoryItem& get()
	{
		static FactoryItem instance;
		return instance;
	}

	void addCreationFunction(const std::string& nameItem, std::function<class Item*(const XMLvariab&)> creationFunction)
	{
		creationFunctions[nameItem] = creationFunction;
	}

protected:
	std::unordered_map<std::string, std::function<class Item*(const XMLvariab&)>> creationFunctions;
};
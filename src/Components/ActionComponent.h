#pragma once

#include <unordered_map>

#include "Action.h"

#include "Time/Timer.h"





struct ActionComponent
{
	int currentAction;
	std::unordered_map<int, Timer> actionDelays;
};
#pragma once

#include <unordered_map>

#include "Time/Timer.h"





enum Actions
{
	NoneActions=-1,
	WalkUp,
	WalkDown,
	WalkRight,
	WalkLeft,
	RotateUp,
	RotateDown,
	RotateRight,
	RotateLeft,
	Observe
};



struct ActionComponent
{
	int currentAction;
	std::unordered_map<int, Timer> actionDelays;
};
#pragma once

#include "Direction.h"

#include "Math/Math.h"





struct BaseEnemyComponent
{
	bool alive;
	int viewDistance;
	std::vector<Direction> path;
	int currentStepPath;
};
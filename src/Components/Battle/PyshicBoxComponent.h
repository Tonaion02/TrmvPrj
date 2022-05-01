#pragma once

#include "Misc/Direction.h"

#include "utils/Math/Math.h"





struct PyshicBoxComponent
{
	Vector2f v;
	float mass;
	Direction lastDirection;
};
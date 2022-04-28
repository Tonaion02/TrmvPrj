#pragma once

#include "Misc/Direction.h"

#include "Math/Math.h"





struct PyshicBoxComponent
{
	Vector2f v;
	float mass;
	Direction lastDirection;
};
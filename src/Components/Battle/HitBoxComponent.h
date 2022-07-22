#pragma once

#include "Time/Timer.h"
#include "Misc/Direction.h"





struct HitBoxComponent
{
	Direction direction;
	Timer delayHitBox;
	float damage;
};
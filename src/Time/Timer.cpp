#include "Time/Timer.h"





void start(Timer* timer)
{
	timer->timePassed = 0.0f;
}



bool isEnd(const Timer& timer)
{
	return timer.timePassed >= timer.coolDown;
}
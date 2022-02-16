#pragma once





struct Timer
{
	float timePassed;
	float coolDown;
};



void start(Timer* timer);
bool isEnd(const Timer& timer);
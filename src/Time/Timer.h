#pragma once





struct Timer
{
	float timePassed;
	float coolDown;
};



void initTimer(Timer* timer);
void start(Timer* timer);
bool isEnd(const Timer& timer);
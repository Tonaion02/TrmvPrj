#include "Math.h"

#include <random>
#include <chrono>





void setRandomGenerator(unsigned int seed)
{
	srand((unsigned int)time(NULL));
}



int random()
{
	return rand();
}
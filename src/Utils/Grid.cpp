#include "Grid.h"





int getIndex2D(const Vector2i& pos, int dimX)
{
	return pos.x + pos.y * dimX;
}



int getIndex3D(const Vector2i& pos, int z, int dimX, int dimZ)
{
	return z + pos.x * dimZ + pos.y * dimX;
}
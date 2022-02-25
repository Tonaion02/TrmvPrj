#include "Direction.h"





Direction reverseDirection(Direction direction)
{
	switch (direction)
	{
	case Up:
		return Down;
	case Down:
		return Up;
	case Right:
		return Left;
	case Left:
		return Right;



	default:
		break;
	}

	return NoneDirection;
}
#pragma once

#include "ECS/System.h"





class MoveSystem : public System
{
public:
	static void move();
protected:
	static bool isValid(const class Vector2f& pos);
};
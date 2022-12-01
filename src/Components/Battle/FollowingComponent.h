#pragma once

#include "utils/Math/Math.h"

#include "ECS/Entity.h"





struct FollowingComponent
{
	Entity parent;
	Vector2i tranformPos;
};
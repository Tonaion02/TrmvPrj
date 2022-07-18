#pragma once

#include "utils/Math/Vector2i.h"

#include "ECS/Entity.h"





struct FollowingComponent
{
	Entity parent;
	Vector2i tranformPos;
};
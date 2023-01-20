#pragma once

#include "Misc/Direction.h"
#include "Components/Exploring/AnimationComponent.h"
#include "Components/Exploring/ActionComponent.h"

#include "ECS/Entity.h"




class AnimationSystem
{
public:
	static void init();
	static void animate();
	static void startAnimation(Entity e);
	static void addAnimation(Entity e, const TiledAnimation& tiledAnimation, Actions action, Direction direction);
};
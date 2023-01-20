#pragma once

#include "ECS/Entity.h"





class InteractionSystem
{
public:
	static void startInteraction(Entity e);
	static void interact();
	static void endInteraction(Entity e);
};
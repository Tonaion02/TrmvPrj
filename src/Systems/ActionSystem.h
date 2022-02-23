#pragma once

#include "ECS/Entity.h"
#include "Components/ActionComponent.h"





class ActionSystem
{
public:
	static void init();
	static void endAction();
	static void updateAction();
	static void startAction(Entity entity,Actions action);
	static bool isDoingNothing(Entity e);
};
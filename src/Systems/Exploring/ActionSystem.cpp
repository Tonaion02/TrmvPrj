#include "ActionSystem.h"

//Including ECS
#include "ECS/ECS.h"
//Including ECS

//Including other systems
#include "Systems/Exploring/MoveSystem.h"
#include "Systems/Exploring/InteractionSystem.h"
//Including other systems

//Including world
#include "Game.h"
#include "World.h"
//Including world





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class ActionSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
void ActionSystem::init()
{
	World* world = Game::get()->getWorld();

	ComponentPool<ActionComponent>* poolActionCmp = &world->mPoolActionComponent;

	for (unsigned int i = 0; i < poolActionCmp->mNext; i++)
	{
		poolActionCmp->mPackedArray[i].currentAction = NoneActions;
	}
}



void ActionSystem::endAction()
{
	World* world = Game::get()->getWorld();

	ComponentPool<ActionComponent>* poolActionCmp = &world->mPoolActionComponent;

	for (unsigned int i = 0; i < poolActionCmp->mNext; i++)
	{
		int currentAction = poolActionCmp->mPackedArray[i].currentAction;

		if (currentAction != NoneActions)
		{		
			if (isEnd(poolActionCmp->mPackedArray[i].actionDelays[currentAction]))
			{
				//Correct termination of action
				switch (currentAction)
				{

				case Walk:
				case Rotate:
					MoveSystem::endMove(poolActionCmp->mDirectArray[i]);
					break;

				case Interact:
					InteractionSystem::endInteraction(poolActionCmp->mDirectArray[i]);
					break;

				default:
					break;
				}
				//Correct termination of action


				//Reset action 
				//poolActionCmp->mPackedArray[i].currentAction = NoneActions;
				getCmpIndex(world->mPoolActionComponent, i).currentAction = NoneActions;
				//Reset action
			}
		}
	}
}



void ActionSystem::updateAction()
{
	World* world = Game::get()->getWorld();
	float deltaTime = Game::get()->getDeltaTime();

	ComponentPool<ActionComponent>& poolActionCmp = world->mPoolActionComponent;

	for (unsigned int i = 0; i < poolActionCmp.mNext; i++)
	{
		if (getCmpIndex(world->mPoolActionComponent, i).currentAction != NoneActions)
		{
			//Update delay of Action
			getCmpIndex(world->mPoolActionComponent, i).actionDelays[getCmpIndex(world->mPoolActionComponent, i).currentAction].timePassed += deltaTime;
			//Update delay of Action
		}
	}
}



void ActionSystem::startAction(Entity e, Actions action)
{
	World* world = Game::get()->getWorld();

	ComponentPool<ActionComponent>& poolActionCmp = world->mPoolActionComponent;

	if (getCmpEntity(world->mPoolActionComponent, e).currentAction == NoneActions)
	{
		getCmpEntity(world->mPoolActionComponent, e).currentAction = action;
		start(&getCmpEntity(world->mPoolActionComponent, e).actionDelays[getCmpEntity(world->mPoolActionComponent, e).currentAction]);
	}
}



bool ActionSystem::isDoingNothing(Entity e)
{
	World* world = Game::get()->getWorld();

	return getCmpEntity(world->mPoolActionComponent, e).currentAction == Actions::NoneActions;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class ActionSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
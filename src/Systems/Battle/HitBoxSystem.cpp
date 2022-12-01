#include "Systems/Battle/HitBoxSystem.h"

#include "ECS/ECS.h"

//Including some context
#include "World.h"
#include "Game.h"
//Including some context





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class HitBoxSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
void HitBoxSystem::init()
{

}



void HitBoxSystem::checkIfIsDead()
{
	World* world = Game::get()->getWorld();

	for (unsigned int i = 0; i < world->mPoolHitBoxComponent.mNext; i++)
	{
		Entity e = world->mPoolHitBoxComponent.mDirectArray[i];

		getCmpIndex(world->mPoolHitBoxComponent, i).delayHitBox.timePassed += Game::get()->getDeltaTime();

		if (isEnd(getCmpIndex(world->mPoolHitBoxComponent, i).delayHitBox))
			deleteEntity(e);
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class HitBoxSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
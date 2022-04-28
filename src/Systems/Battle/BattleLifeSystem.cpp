#include "BattleLifeSystem.h"

//Including some context
#include "Game.h"
#include "World.h"
//Including some context





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class LifeSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
void LifeSystem::init()
{

}



void LifeSystem::onCollision()
{

}



void LifeSystem::checkIfIsDead()
{
	World* world = Game::get()->getWorld();

	for (unsigned int i = 0; i < world->mPoolLifeBarComponent.mNext; i++)
	{
		Entity e = world->mPoolLifeBarComponent.mDirectArray[i];

		if (world->mPoolLifeBarComponent.mPackedArray[i].health <= 0.0f)
		{
			//destroy the dead entities
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class LifeSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
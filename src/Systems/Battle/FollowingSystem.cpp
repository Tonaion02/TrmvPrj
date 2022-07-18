#include "Systems/Battle/FollowingSystem.h"

#include "utils/Physic/GridSP.h"

#include "ECS/ECS.h"

//Including some context
#include "Game.h"
#include "World.h"
//Including some context





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class FollowingSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
void FollowingSystem::update()
{
	World* world = Game::get()->getWorld();

	for (unsigned int i = 0; i < world->mPoolFollowingComponent.mNext; i++)
	{
		Entity e = world->mPoolFollowingComponent.mDirectArray[i];

		Entity parent = world->mPoolFollowingComponent.mPackedArray[i].parent;
		
		getCmpEntity(&world->mPoolTransformBattleComponent, e)->pos = getCmpEntity(&world->mPoolTransformBattleComponent, parent)->pos + world->mPoolFollowingComponent.mPackedArray[i].tranformPos;
	
		unRegisterEntity(e, world->currentLevel.battleCamp.gridSP);
		registerEntity(e, world->currentLevel.battleCamp.gridSP);
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class FollowingSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
#include "Systems/Exploring/InteractionSystem.h"

//Including ECS
#include "ECS/ECS.h"
//Including ECS

//Including other systems
#include "Systems/Exploring/ActionSystem.h"
#include "Systems/Exploring/TileSystem.h"
//Including other systems

//Including some context
#include "World.h"
#include "Game.h"
//Including some context





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class InteractionSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
void InteractionSystem::startInteraction(Entity e)
{
	Game* gameInstance = Game::get();
	World* world = Game::get()->getWorld();

	ComponentPool<TransformComponent>& TransformCmp = world->mPoolTransformComponent;
	ComponentPool<MoveComponent>& MoveCmp = world->mPoolMoveComponent;
	ComponentPool<ActionComponent>& ActionCmp = world->mPoolActionComponent;

	Vector2i pos = getCmpEntity(TransformCmp, e).pos;
	int z = getCmpEntity(TransformCmp, e).z;
	Direction dir = static_cast<Direction>(getCmpEntity(MoveCmp, e).lastDirection);
	getCmpEntity(MoveCmp, e).currentDirection = dir;

	if (getCmpEntity(ActionCmp, e).currentAction == Actions::Interact)
	{
		switch (dir)
		{
		case NoneDirection:
			break;

		case Up:
			pos.y -= 1;
			break;
		case Down:
			pos.y += 1;
			break;
		case Right:
			pos.x += 1;
			break;
		case Left:
			pos.x -= 1;
			break;
		
		default:
			break;
		}



		if (!TileSystem::isInteractable(pos, z))
		{
			getCmpEntity(ActionCmp, e).currentAction = Actions::NoneActions;
		}
	}
}



void InteractionSystem::endInteraction(Entity e)
{
	World* world = Game::get()->getWorld();
	
	Direction dir = static_cast<Direction>(getCmpEntity(world->mPoolMoveComponent, e).lastDirection);
	Vector2i pos = getCmpEntity(world->mPoolTransformComponent, e).pos;

	switch (dir)
	{
	case NoneDirection:
		break;

	case Up:
		pos.y -= 1;
		break;
	case Down:
		pos.y += 1;
		break;
	case Right:
		pos.x += 1;
		break;
	case Left:
		pos.x -= 1;
		break;

	default:
		break;
	}

	TileSystem::interactReaction(pos, getCmpEntity(world->mPoolTransformComponent, e).z);
}



void InteractionSystem::interact()
{

}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class InteractionSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
#include "Systems/Exploring/MoveSystem.h"

//Include World
#include "Game.h"
#include "World.h"
//Include World

//Include some base ECS
#include "ECS/Entity.h"
#include "ECS/ComponentPool.h"
#include "ECS/ECS.h"
//Include some base ECS

//Including Components
#include "Components/Exploring/MoveComponent.h"
#include "Components/Exploring/TransformComponent.h"
//Including Components

//Including other Systems
#include "Systems/Exploring/TileSystem.h"
//Including other Systems





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class MoveSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
void MoveSystem::move()
{
	Game* gameInstance = Game::get();
	World* world = Game::get()->getWorld();

	ComponentPool<TransformComponent>& TransformCmp = world->mPoolTransformComponent;
	ComponentPool<MoveComponent>& MoveCmp = world->mPoolMoveComponent;
	ComponentPool<ActionComponent>& ActionCmp = world->mPoolActionComponent;

	float deltaTime = Game::get()->getDeltaTime();

	for (unsigned int i = 0; i < MoveCmp.mNext; i++)
	{
		Entity e = MoveCmp.mDirectArray[i];

		float incr;
		switch (ActionCmp.mPackedArray[ActionCmp.mReverseArray[e]].currentAction)
		{
		case Walk:
			incr = 1.0f / (ActionCmp.mPackedArray[ActionCmp.mReverseArray[e]].actionDelays[Walk].coolDown);
			switch (MoveCmp.mPackedArray[i].currentDirection)
			{
			case Up:
				TransformCmp.mPackedArray[TransformCmp.mReverseArray[e]].pos.y -= incr * deltaTime;
				break;
			case Down:
				TransformCmp.mPackedArray[TransformCmp.mReverseArray[e]].pos.y += incr * deltaTime;
				break;
			case Right:
				TransformCmp.mPackedArray[TransformCmp.mReverseArray[e]].pos.x += incr * deltaTime;
				break;
			case Left:
				TransformCmp.mPackedArray[TransformCmp.mReverseArray[e]].pos.x -= incr * deltaTime;
				break;
			default:
				break;
			}

			break;
		default:
			break;
		}
	}
}



void MoveSystem::endMove(Entity e)
{
	Game* gameInstance = Game::get();
	World* world = Game::get()->getWorld();

	ComponentPool<MoveComponent>& MoveCmp = world->mPoolMoveComponent;
	ComponentPool<TransformComponent>& TransformCmp = world->mPoolTransformComponent;

	//Fix position
	TransformCmp.mPackedArray[TransformCmp.mReverseArray[e]].pos = static_cast<Vector2f>(TransformCmp.mPackedArray[TransformCmp.mReverseArray[e]].tileOccupied);
	//Fix position

	//Set lastDirection to currentDirection
	MoveCmp.mPackedArray[MoveCmp.mReverseArray[e]].lastDirection = MoveCmp.mPackedArray[MoveCmp.mReverseArray[e]].currentDirection;
	//Set lastDirection to currentDirection

	//Reset currentDirection
	MoveCmp.mPackedArray[MoveCmp.mReverseArray[e]].currentDirection = NoneDirection;
	//Reset currentDirection
}



void MoveSystem::startMove(Entity e, Direction direction)
{
	Game* gameInstance = Game::get();
	World* world = Game::get()->getWorld();

	ComponentPool<TransformComponent>& TransformCmp = world->mPoolTransformComponent;
	ComponentPool<MoveComponent>& MoveCmp = world->mPoolMoveComponent;
	ComponentPool<ActionComponent>& ActionCmp = world->mPoolActionComponent;

	//Vector2i pos = TransformCmp->mPackedArray[TransformCmp->mReverseArray[e]].pos;
	Vector2i pos = getCmpEntity(TransformCmp, e).pos;
	//MoveCmp->mPackedArray[MoveCmp->mReverseArray[e]].currentDirection = direction;
	getCmpEntity(MoveCmp, e).currentDirection = direction;

	//switch (ActionCmp->mPackedArray[ActionCmp->mReverseArray[e]].currentAction)
	switch (getCmpEntity(ActionCmp, e).currentAction)
	{
	case Walk:
		//switch (MoveCmp->mPackedArray[MoveCmp->mReverseArray[e]].currentDirection)
		switch (getCmpEntity(MoveCmp, e).currentDirection)
		{
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
		break;

	default:
		break;
	}



	//If the currentDirection is equal to the lastdirection do move
	if (MoveCmp.mPackedArray[MoveCmp.mReverseArray[e]].lastDirection != direction)
	{
		switch (direction)
		{
		case Up:
			ActionCmp.mPackedArray[ActionCmp.mReverseArray[e]].currentAction = Rotate;
			break;
		case Down:
			ActionCmp.mPackedArray[ActionCmp.mReverseArray[e]].currentAction = Rotate;
			break;
		case Right:
			ActionCmp.mPackedArray[ActionCmp.mReverseArray[e]].currentAction = Rotate;
			break;
		case Left:
			ActionCmp.mPackedArray[ActionCmp.mReverseArray[e]].currentAction = Rotate;
			break;
		default:
			break;
		}

		start(&ActionCmp.mPackedArray[ActionCmp.mReverseArray[e]].actionDelays[ActionCmp.mPackedArray[ActionCmp.mReverseArray[e]].currentAction]);
	}
	//If the currentDirection is equal to the lastdirection do move



	//If the currentDirection is not equal to the lastdirection do rotation
	else
	{
		if (MoveSystem::isValid(pos, TransformCmp.mPackedArray[TransformCmp.mReverseArray[e]].z))
		{
			TileSystem::unRegisterPos(TransformCmp.mPackedArray[TransformCmp.mReverseArray[e]].tileOccupied, TransformCmp.mPackedArray[TransformCmp.mReverseArray[e]].z);
			TileSystem::registerPos(pos, TransformCmp.mPackedArray[TransformCmp.mReverseArray[e]].z, e);
			TransformCmp.mPackedArray[TransformCmp.mReverseArray[e]].tileOccupied = pos;
			start(&ActionCmp.mPackedArray[ActionCmp.mReverseArray[e]].actionDelays[ActionCmp.mPackedArray[ActionCmp.mReverseArray[e]].currentAction]);
		}
		else
		{
			ActionCmp.mPackedArray[ActionCmp.mReverseArray[e]].currentAction = NoneActions;
		}
	}
	//If the currentDirection is not equal to the lastdirection do rotation
}



bool MoveSystem::isValid(const Vector2f& pos, short int z)
{
	World* world = Game::get()->getWorld();

	//Controll if is in the range of the level the position
	if (pos.x < 0.0f 
		|| pos.x > world->currentLevel.dim.x-1
		|| pos.y < 0.0f
		|| pos.y > world->currentLevel.dim.y-1)
		return false;
	//Controll if is in the range of the level the position



	//Controll if isWalkable the tile
	if (!TileSystem::isWalkable(static_cast<Vector2f>(pos), z))
		return false;
	//Controll if isWalkable the tile


	
	//Controll if there is another Entity on that position
	if (TileSystem::isOccupied(static_cast<Vector2f>(pos), z))
		return false;
	//Controll if there is another Entity on that position



	//If all is good return true
	return true;
	//If all is good return true
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class MoveSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
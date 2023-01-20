#include "AnimationSystem.h"

//Including components
#include "Components/Exploring/AnimationComponent.h"
#include "Components/Exploring/DrawComponent.h"
#include "Components/Exploring/MoveComponent.h"
//Including components

//Including world
#include "Game.h"
#include "World.h"
//Including world





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class AnimationSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
void AnimationSystem::init()
{
	World* world = Game::get()->getWorld();

	ComponentPool<AnimationComponent>* animationCmp = &world->mPoolAnimationComponent;
	ComponentPool<DrawComponent>* drawCmp = &world->mPoolDrawComponent;
	ComponentPool<ActionComponent>* actionCmp = &world->mPoolActionComponent;

	for (unsigned int i = 0; i < world->mPoolAnimationComponent.mNext; i++)
	{
		Entity e = animationCmp->mDirectArray[i];
	
		for (auto groupAnimation = animationCmp->mPackedArray[i].animations.begin(); groupAnimation != animationCmp->mPackedArray[i].animations.end(); groupAnimation++)
		{
			animationCmp->mPackedArray[i].currentId = 0.0f;

			for (auto animation = groupAnimation->second.begin(); animation != groupAnimation->second.end(); animation++)
			{
				if (animation->second.ids.size() == 1)
				{
					animation->second.incrementIndex = 1.0f;
				}
				else
				{
					animation->second.incrementIndex = animation->second.ids.size() / 
						(actionCmp->mPackedArray[actionCmp->mReverseArray[e]].actionDelays[groupAnimation->first].coolDown * 1000.0f);
				}
			}
		}
	}
}



void AnimationSystem::addAnimation(Entity e, const TiledAnimation& tiledAnimation, Actions action, Direction direction)
{
	World* world = Game::get()->getWorld();

	ComponentPool<AnimationComponent>* animationCmp = &world->mPoolAnimationComponent;

	animationCmp->mPackedArray[animationCmp->mReverseArray[e]].animations[action][direction] = tiledAnimation;
}



void AnimationSystem::animate()
{
	World* world = Game::get()->getWorld();
	float deltaTime = Game::get()->getDeltaTime();

	ComponentPool<AnimationComponent>* animationCmp = &world->mPoolAnimationComponent;
	ComponentPool<DrawComponent>* drawCmp = &world->mPoolDrawComponent;
	ComponentPool<ActionComponent>* actionCmp = &world->mPoolActionComponent;
	ComponentPool<MoveComponent>* moveCmp = &world->mPoolMoveComponent;

	for (unsigned int i = 0; i < world->mPoolAnimationComponent.mNext; i++)
	{
		Entity e = animationCmp->mDirectArray[i];
		
		Actions action = static_cast<Actions>(actionCmp->mPackedArray[actionCmp->mReverseArray[e]].currentAction);

		Direction direction = (Direction)moveCmp->mPackedArray[moveCmp->mReverseArray[e]].lastDirection;

		//TO FIX
		if (action != Actions::NoneActions)
		{
			direction = (Direction)moveCmp->mPackedArray[moveCmp->mReverseArray[e]].currentDirection;
		}
		//TO FIX

		auto iterGroup = animationCmp->mPackedArray[i].animations.find(action);
		auto iter = iterGroup->second.find(direction);

		animationCmp->mPackedArray[i].currentId += iter->second.incrementIndex * deltaTime * 1000.0f;
		if (animationCmp->mPackedArray[i].currentId >= iter->second.ids.size() - 1)
			animationCmp->mPackedArray[i].currentId = static_cast<float>(iter->second.ids.size() - 1);
		drawCmp->mPackedArray[drawCmp->mReverseArray[e]].id = iter->second.ids[static_cast<int>(animationCmp->mPackedArray[i].currentId)];
	}
}



void AnimationSystem::startAnimation(Entity e)
{
	World* world = Game::get()->getWorld();
	float deltaTime = Game::get()->getDeltaTime();

	ComponentPool<AnimationComponent>* animationCmp = &world->mPoolAnimationComponent;
	ComponentPool<ActionComponent>* actionCmp = &world->mPoolActionComponent;

	Actions action = static_cast<Actions>(actionCmp->mPackedArray[actionCmp->mReverseArray[e]].currentAction);
	if (action != NoneActions)
	{
		animationCmp->mPackedArray[animationCmp->mReverseArray[e]].currentId = 0.0f;
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class AnimationSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
#include "AnimationSystem.h"

//Including components
#include "Components/ActionComponent.h"
#include "Components/AnimationComponent.h"
#include "Components/DrawComponent.h"
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
		
		for (auto animation = animationCmp->mPackedArray[i].animations.begin(); animation != animationCmp->mPackedArray[i].animations.end(); animation++)
		{
			animationCmp->mPackedArray[i].currentId = 0.0f;
			if (animation->first != NoneActions)
			{
				animation->second.incrementIndex = animation->second.ids.size() /
					(actionCmp->mPackedArray[actionCmp->mReverseArray[e]].actionDelays[animation->first].coolDown * 1000.0f);
			}
			else
			{
				animation->second.incrementIndex = 1.0f;
			}
			int wewe = 0;
		}
	}
}



void AnimationSystem::animate()
{
	World* world = Game::get()->getWorld();
	float deltaTime = Game::get()->getDeltaTime();

	ComponentPool<AnimationComponent>* animationCmp = &world->mPoolAnimationComponent;
	ComponentPool<DrawComponent>* drawCmp = &world->mPoolDrawComponent;
	ComponentPool<ActionComponent>* actionCmp = &world->mPoolActionComponent;

	for (unsigned int i = 0; i < world->mPoolAnimationComponent.mNext; i++)
	{
		Entity e = animationCmp->mDirectArray[i];
		
		Actions action = static_cast<Actions>(actionCmp->mPackedArray[actionCmp->mReverseArray[e]].currentAction);

		auto iter = animationCmp->mPackedArray[i].animations.find(action);

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
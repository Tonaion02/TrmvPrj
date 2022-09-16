#include "Scenes/ExploringScene.h"

//Including ECS
#include "ECS/ECS.h"
//Including ECS

//Including some context
#include "World.h"
#include "Game.h"
//Including some context

//Including Scenes
#include "Scenes/BattleScene.h"
#include "Scenes/GeneralMenuScene.h"
//Including Scenes

//Including some Enviroment
#include "Enviroment/WindowHandler.h"

#include "Enviroment/Input/Input.h"
//Including some Enviroment

//Including Systems
#include "Systems/MoveSystem.h"
#include "Systems/AnimationSystem.h"
#include "Systems/InteractionSystem.h"

#include "Systems/CameraSystem.h"
#include "Systems/ActionSystem.h"
#include "Systems/EnemySystem.h"
#include "Systems/RenderSystem.h"
//Including Systems





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class ExploringScene
//-----------------------------------------------------------------------------------------------------------------------------------------
ExploringScene::ExploringScene()
	:BaseScene(idTypeScenes<ExploringScene>())
{

}



void ExploringScene::updateScene()
{
	World* world = getWorld();

	if (status == statusScene::RunningScene)
	{
		//First input and then AI decides what is the action

		//Execute current action of all Entity
		MoveSystem::move();
		InteractionSystem::interact();

		AnimationSystem::animate();

		CameraSystem::updateCamera(world->mPoolTransformComponent.mPackedArray[
			world->mPoolTransformComponent.mReverseArray[world->player]].pos);
		//Execute current action of all Entity

		//Update Component
		ActionSystem::updateAction();
		//Update Component

		//Update debugInfoTimer
		if (!isEnd(world->debugInfoTimer))
		{
			world->debugInfoTimer.timePassed += getGame()->getDeltaTime();
		}
		//Update debugInfoTimer

		//Controll if the action is ended
		ActionSystem::endAction();
		//Controll if the action is ended

		//Now the action that is ended is set to NoneAction
		EnemySystem::aiBaseEnemy();
	}
}



void ExploringScene::loadScene()
{

}



void ExploringScene::generateOutputScene()
{
	//Prepare rendering
	RenderSystem::draw();
	//Prepare rendering
}



void ExploringScene::processInputScene()
{
	const Uint8* keyStates = SDL_GetKeyboardState(nullptr);

	if (status == RunningScene)
	{
		if (isResizedWindow())
		{
			SDL_Log("Window size changed to %dx%d", getWindowSize().x, getWindowSize().y);
			WindowHandler::get().updateWindowDimension(getWindowSize());
			CameraSystem::onUpdateWindowSize();
		}
		if (isQuitted())
		{
			Game::get()->setRunning(false);
		}
		if (isPressedKey(SDL_SCANCODE_M))
		{
			consumeClick(SDL_SCANCODE_M);
			if (!isActiveScene<GeneralMenuScene>())
			{
				Game::get()->startGeneralMenu();
				Game::get()->getGeneraMenuScene()->choice = 0;
			}
		}



		//For moving player
		if (keyStates[SDL_SCANCODE_W])
		{
			if (ActionSystem::isDoingNothing(world->player) && world->battleEntities.empty())
			{
				ActionSystem::startAction(world->player, Actions::Walk);
				MoveSystem::startMove(world->player, Direction::Up);
				AnimationSystem::startAnimation(world->player);
			}
		}
		else if (keyStates[SDL_SCANCODE_S] && world->battleEntities.empty())
		{
			if (ActionSystem::isDoingNothing(world->player))
			{
				ActionSystem::startAction(world->player, Actions::Walk);
				MoveSystem::startMove(world->player, Direction::Down);
				AnimationSystem::startAnimation(world->player);
			}
		}
		else if (keyStates[SDL_SCANCODE_D] && world->battleEntities.empty())
		{
			if (ActionSystem::isDoingNothing(world->player))
			{
				ActionSystem::startAction(world->player, Actions::Walk);
				MoveSystem::startMove(world->player, Direction::Right);
				AnimationSystem::startAnimation(world->player);
			}
		}
		else if (keyStates[SDL_SCANCODE_A] && world->battleEntities.empty())
		{
			if (ActionSystem::isDoingNothing(world->player))
			{
				ActionSystem::startAction(world->player, Actions::Walk);
				MoveSystem::startMove(world->player, Direction::Left);
				AnimationSystem::startAnimation(world->player);
			}
		}
		//For moving player

		//For interaction of the player
		else if (keyStates[SDL_SCANCODE_B] && world->battleEntities.empty())
		{
			if (ActionSystem::isDoingNothing(world->player))
			{
				ActionSystem::startAction(world->player, Actions::Interact);
				InteractionSystem::startInteraction(world->player);
				AnimationSystem::startAnimation(world->player);
			}
		}
		//For interaction of the player



		//For debuggingInfo
		else if (keyStates[SDL_SCANCODE_3] && isEnd(world->debugInfoTimer))
		{
			SDL_Log(
				"Player pos: ( %f, %f )",
				getCmpEntity(&world->mPoolTransformComponent, world->player)->pos.x,
				getCmpEntity(&world->mPoolTransformComponent, world->player)->pos.y
			);

			start(&world->debugInfoTimer);
		}
		//For debuggingInfo



		//For startingBattle
		else if (keyStates[SDL_SCANCODE_4])
		{
			static bool first = true;

			game->startBattle();

			first = false;
		}
		//For startingBattle
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class ExploringScene
//-----------------------------------------------------------------------------------------------------------------------------------------
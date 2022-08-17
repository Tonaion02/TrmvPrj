#include "Scenes/ExploringScene.h"

#include "ECS/ECS.h"

#include "Enviroment/WindowHandler.h"

#include "Systems/MoveSystem.h"
#include "Systems/AnimationSystem.h"
#include "Systems/CameraSystem.h"
#include "Systems/ActionSystem.h"
#include "Systems/EnemySystem.h"
#include "Systems/RenderSystem.h"

#include "World.h"
#include "Game.h"

///TESTING MENU
#include "Enviroment/TextureHandler.h"
#include "Menu/General/ImageWidget.h"
#include "Menu/General/ContainerWidget.h"
#include "Menu/General/ButtonWidget.h"

#include "Menu/ExploringMenu/GeneralExploringMenu.h"

#include "Menu/ExploringMenu/TestMenu.h"

#include "Input/Input.h"
///TESTING MENU





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

	if (status == RunningScene)
	{
		//First input and then AI decides what is the action

		//Execute current action of all Entity
		MoveSystem::move();

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



		///FOR TESTING
		if(showMenu)
			widget->update();
		///FOR TESTING
	}
}



void ExploringScene::loadScene()
{
	///FOR TESTING
	
	showMenu = false;
	
	///Creating menu
	std::array<DrawableWidget*, 5> buttons;
	for (int i = 0; i < buttons.size(); i++)
	{
		ImageWidget* background = new ImageWidget(TextureHandler::get().getTexture("data/buch-outdoor.png"), Vector2i(0, 0), Vector2i(50, 50));
		background->init();
		ImageWidget* child = new ImageWidget(TextureHandler::get().getTexture("data/player.png"), Vector2i(0, 0), Vector2i(20, 20));
		child->init();
		ContainerWidget* container = new ContainerWidget(background, child, Vector2i(5, 5));
		container->init();

		ButtonWidget* button = new ButtonWidget(Vector2i(0, 0), Vector2i(50, 50), container);
		button->init();
		button->setFunction(changePage);
		buttons[i] = button;
	}
	VerticalGroupWidget<LIMITS_CHILDREN_TEST_MENU>* vGroup = new VerticalGroupWidget<LIMITS_CHILDREN_TEST_MENU>({ 0, 0 }, buttons);
	vGroup->init();

	ImageWidget* backgroundForMenu = new ImageWidget(TextureHandler::get().getTexture("data/buch-outdoor.png"), Vector2i(0, 0), Vector2i(300, 300));
	backgroundForMenu->init();
	TestMenu<LIMITS_CHILDREN_TEST_MENU>* ptr = new TestMenu<LIMITS_CHILDREN_TEST_MENU>(backgroundForMenu, vGroup);
	ptr->init();
	widget = ptr;



	///TRYING TO MOVE MENU
	widget->setPos({ 300, 0 });
	///TRYING TO MOVE MENU

	///Creating menu

	///FOR TESTING
}



void ExploringScene::generateOutputScene()
{
	if (status == RunningScene)
	{
		//Prepare rendering
		RenderSystem::draw();
		//Prepare rendering

		if(showMenu)
			widget->draw();
	}
}



void ExploringScene::processInputScene()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			Game::get()->setRunning(false);
			break;
		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				SDL_Log("Window %d size changed to %dx%d", event.window.windowID, event.window.data1, event.window.data2);
				WindowHandler::get().updateWindowDimension({ event.window.data1, event.window.data2 });
				CameraSystem::onUpdateWindowSize();
				break;
			}
			break;
		case SDL_KEYDOWN:
			{
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_M:
					showMenu = !showMenu;

				default:
					break;
				}
			}
		}
	}

	updateInput();

	const Uint8* keyStates = SDL_GetKeyboardState(nullptr);

	if (status == RunningScene)
	{
		//For debugging
		if (keyStates[SDL_SCANCODE_B])
		{

		}
		//For debugging



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
		else if (keyStates[SDL_SCANCODE_D])
		{
			if (ActionSystem::isDoingNothing(world->player) && world->battleEntities.empty())
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



		//For debuggingInfo
		else if (keyStates[SDL_SCANCODE_3] && isEnd(world->debugInfoTimer))
		{
			SDL_Log(
				"Player pos: ( %f, %f )",
				world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[world->player]].pos.x,
				world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[world->player]].pos.y
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

		//else if (keyStates[SDL_SCANCODE_M])
		//	showMenu = !showMenu;
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class ExploringScene
//-----------------------------------------------------------------------------------------------------------------------------------------
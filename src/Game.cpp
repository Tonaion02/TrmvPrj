#include "Game.h"

//Including Generals
#include "Direction.h"
#include "Data/Phase/Phase.h"
#include "Data/Phase/PhaseHandler.h"
//Including Generals

//Including Enviroment
#include "Enviroment/WindowHandler.h"
#include "Enviroment/TextureHandler.h"
//Including Enviroment

//Including Utils
#include "Utils/Grid.h"
//Including Utils

//Including Ecs
#include "ECS/Family.h"
#include "ECS/EntityManager.h"
#include "ECS/ComponentManager.h"
#include "ECS/System.h"
//Including Ecs

//Including System
#include "Systems/RenderSystem.h"
#include "Systems/MoveSystem.h"
#include "Systems/CameraSystem.h"
#include "Systems/ActionSystem.h"
#include "Systems/AnimationSystem.h"
#include "Systems/TileSystem.h"
#include "Systems/EnemySystem.h"
//Including System

//Some Shit
#include "World.h"
//Some Shit





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class Game
//-----------------------------------------------------------------------------------------------------------------------------------------
const float Game::sMaxDeltaTime = 0.5f;
Game* Game::sGameInstance = nullptr;





void Game::update()
{
	for (auto iter : mWorld->phaseHandler.phaseStack)
	{
		if (iter->phaseType == PhaseType::Exploring)
		{
			if (iter->statePhase == StatePhase::On)
			{
				//First input and then AI decides what is the action

				//Execute current action of all Entity
				MoveSystem::move();

				AnimationSystem::animate();

				CameraSystem::updateCamera();
				//Execute current action of all Entity

				//Update Component
				ActionSystem::updateAction();
				//Update Component

				//Update debugInfoTimer
				if (!isEnd(mWorld->debugInfoTimer))
				{
					mWorld->debugInfoTimer.timePassed += mDeltaTime;
				}
				//Update debugInfoTimer

				//Controll if the action is ended
				ActionSystem::endAction();
				//Controll if the action is ended

				//Now the action that is ended is set to NoneAction
				EnemySystem::aiBaseEnemy();
			}
		}
		else if (iter->phaseType == PhaseType::Battle)
		{

		}
	}

}



void Game::processInput()
{
	SDL_Event event;

	//Handle events
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
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
		}
	}
	//Handle events

	const Uint8* keyStates = SDL_GetKeyboardState(nullptr);



	//For zooming camera in and out
	if (keyStates[SDL_SCANCODE_1])
	{
		CameraSystem::updateCameraZoom(1.0f);
	}
	if (keyStates[SDL_SCANCODE_2])
	{
		CameraSystem::updateCameraZoom(-1.0f);
	}
	//For zooming camera in and out



	//For moving player
	if (keyStates[SDL_SCANCODE_W])
	{
		if (ActionSystem::isDoingNothing(mWorld->player))
		{
			ActionSystem::startAction(mWorld->player, Actions::Walk);
			MoveSystem::startMove(mWorld->player, Direction::Up);
			AnimationSystem::startAnimation(mWorld->player);
		}
	}
	else if (keyStates[SDL_SCANCODE_S])
	{
		if (ActionSystem::isDoingNothing(mWorld->player))
		{
			ActionSystem::startAction(mWorld->player, Actions::Walk);
			MoveSystem::startMove(mWorld->player, Direction::Down);
			AnimationSystem::startAnimation(mWorld->player);
		}
	}
	else if (keyStates[SDL_SCANCODE_D])
	{
		if (ActionSystem::isDoingNothing(mWorld->player))
		{
			ActionSystem::startAction(mWorld->player, Actions::Walk);
			MoveSystem::startMove(mWorld->player, Direction::Right);
			AnimationSystem::startAnimation(mWorld->player);
		}
	}
	else if (keyStates[SDL_SCANCODE_A])
	{
		if (ActionSystem::isDoingNothing(mWorld->player))
		{
			ActionSystem::startAction(mWorld->player, Actions::Walk);
			MoveSystem::startMove(mWorld->player, Direction::Left);
			AnimationSystem::startAnimation(mWorld->player);
		}
	}
	//For moving player



	//For debuggingInfo
	else if (keyStates[SDL_SCANCODE_3] && isEnd(mWorld->debugInfoTimer))
	{
		SDL_Log(
			"Player pos: ( %f, %f )",
			mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[mWorld->player]].pos.x,
			mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[mWorld->player]].pos.y
		);
		
		start(&mWorld->debugInfoTimer);
	}
	//For debuggingInfo



	//For startingBattle
	else if (keyStates[SDL_SCANCODE_4])
	{
		static bool first = true;

		Game::startBattle();

		first = false;
	}
	//For startingBattle
}



void Game::generateOutput()
{
	//Clean screen
	SDL_RenderClear(WindowHandler::get().getRenderer());
	//Clean screen



	for (auto iter : mWorld->phaseHandler.phaseStack)
	{
		if (iter->phaseType == PhaseType::Exploring)
		{
			if (iter->statePhase != StatePhase::Paused)
			{
				//Prepare rendering
				RenderSystem::draw();
				//Prepare rendering
			}
		}
		else if (iter->phaseType == PhaseType::Battle)
		{
			//Here code to draw battle graphic element
		}
	}



	//Render elements
	SDL_RenderPresent(WindowHandler::get().getRenderer());
	//Render elements
}



void Game::loadData()
{
	//Init some base data
	mIsRunning = true;

	mVsync = false;

	mDeltaTime = 0.0f;
	mTicksCount = 0.0f;
	//Init some base data



	//Init world
	mWorld = new World();
	//Init world



	//Load TileSet and Texture
	mWorld->currentLevel.texture = TextureHandler::get().getTexture("data/buch-outdoor.png");
	mWorld->mTileSetHandler.loadTileSet("data/buch-outdoor.png");
	mWorld->currentLevel.tileSet = *mWorld->mTileSetHandler.getTileSet("data/buch-outdoor.png");
	mWorld->textureActor = TextureHandler::get().getTexture("data/player.png");
	mWorld->mTileSetHandler.loadTileSet("data/player.png");
	mWorld->tilesetActor = mWorld->mTileSetHandler.getTileSet("data/player.png");
	//Load TileSet and Texture



	//Load Level	
	mWorld->currentLevel = levelWrapper("casual generate level");
	//Load Level



	///FOR TESTING

	//Init debugTimer
	mWorld->debugInfoTimer.coolDown = 1.0f;
	initTimer(&mWorld->debugInfoTimer);
	//Init debugTimer

	float x = 0.0f;
	short int z = 0;

	for (int i = 0; i < 5; i++)
	{
		Entity e = EntityManager::get().createEntity();

		registerEntity(&mWorld->mPoolTransformComponent, e);
		mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[e]].pos = { x, x };
		mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[e]].tileOccupied = { (int)x, (int)x };
		mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[e]].z = z;
		registerEntity(&mWorld->mPoolDrawComponent, e);
		mWorld->mPoolDrawComponent.mPackedArray[mWorld->mPoolDrawComponent.mReverseArray[e]].id = 17;

		if (e != 1)
		{
			TileSystem::registerPos({ (int)x,(int)x }, z, e);

			registerEntity(&mWorld->mPoolMoveComponent, e);
			mWorld->mPoolMoveComponent.mPackedArray[mWorld->mPoolMoveComponent.mReverseArray[e]].currentDirection = NoneDirection;
			mWorld->mPoolMoveComponent.mPackedArray[mWorld->mPoolMoveComponent.mReverseArray[e]].lastDirection = Direction::Right;

			registerEntity(&mWorld->mPoolActionComponent, e);
			mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[e]].currentAction = NoneActions;
			mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[e]].actionDelays[Actions::Walk].coolDown = 0.5f;
			mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[e]].actionDelays[Actions::Rotate].coolDown = 0.5f;

			registerEntity(&mWorld->mPoolAnimationComponent, e);
			TiledAnimation tiledAnimation;
			tiledAnimation.ids = { 17 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::NoneActions, Direction::Up);
			tiledAnimation.ids = { 20 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::NoneActions, Direction::Down);
			tiledAnimation.ids = { 26 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::NoneActions, Direction::Right);
			tiledAnimation.ids = { 23 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::NoneActions, Direction::Left);

			tiledAnimation.ids = { 18, 19 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::Walk, Direction::Up);
			tiledAnimation.ids = { 21, 22 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::Walk, Direction::Down);
			tiledAnimation.ids = { 27, 28 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::Walk, Direction::Right);
			tiledAnimation.ids = { 24, 25 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::Walk, Direction::Left);

			tiledAnimation.ids = { 17 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::Rotate, Direction::Up);
			tiledAnimation.ids = { 20 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::Rotate, Direction::Down);
			tiledAnimation.ids = { 26 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::Rotate, Direction::Right);
			tiledAnimation.ids = { 23 };
			AnimationSystem::addAnimation(e, tiledAnimation, Actions::Rotate, Direction::Left);
		}
		
		if (e == 2)
		{
			registerEntity(&mWorld->mPoolBaseEnemyComponent, e);

			std::vector<Direction> path;
			path.push_back(Direction::Right);
			path.push_back(Direction::Right);
			path.push_back(Direction::Down);
			path.push_back(Direction::Right);
			path.push_back(Direction::Right);
			path.push_back(Direction::Right);
			path.push_back(Direction::Down);
			path.push_back(Direction::Down);

			mWorld->mPoolBaseEnemyComponent.mPackedArray[mWorld->mPoolBaseEnemyComponent.mReverseArray[e]].path = path;
		}

		x += 1.0f;
	}



	mWorld->player = 1;

	TileSystem::unRegisterPos(mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[mWorld->player]].tileOccupied, z);
	mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[mWorld->player]].pos = { 7.0f, 1.0f };
	mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[mWorld->player]].tileOccupied =
		mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[mWorld->player]].pos;
	TileSystem::registerPos(mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[mWorld->player]].tileOccupied, z, mWorld->player);

	registerEntity(&mWorld->mPoolMoveComponent, mWorld->player);
	mWorld->mPoolMoveComponent.mPackedArray[mWorld->mPoolMoveComponent.mReverseArray[mWorld->player]].currentDirection = NoneDirection;
	mWorld->mPoolMoveComponent.mPackedArray[mWorld->mPoolMoveComponent.mReverseArray[mWorld->player]].lastDirection = Direction::Down;

	///Register and init entity to PoolActionComponent
	registerEntity(&mWorld->mPoolActionComponent, mWorld->player);

	mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[mWorld->player]].currentAction = NoneActions;

	mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[mWorld->player]].actionDelays[Actions::Walk].coolDown = 0.1f;
	mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[mWorld->player]].actionDelays[Actions::Rotate].coolDown = 0.5f;
	///Register and init entity to PoolActionComponent

	///Register and init entity to poolAnimationComponent
	registerEntity(&mWorld->mPoolAnimationComponent, mWorld->player);

	TiledAnimation tiledAnimation;

	tiledAnimation.ids = { 17 };
	AnimationSystem::addAnimation(mWorld->player, tiledAnimation, Actions::NoneActions, Direction::Up);
	tiledAnimation.ids = { 20 };
	AnimationSystem::addAnimation(mWorld->player, tiledAnimation, Actions::NoneActions, Direction::Down);
	tiledAnimation.ids = { 26 };
	AnimationSystem::addAnimation(mWorld->player, tiledAnimation, Actions::NoneActions, Direction::Right);
	tiledAnimation.ids = { 23 };
	AnimationSystem::addAnimation(mWorld->player, tiledAnimation, Actions::NoneActions, Direction::Left);

	tiledAnimation.ids = { 18, 19 };
	AnimationSystem::addAnimation(mWorld->player, tiledAnimation, Actions::Walk, Direction::Up);
	tiledAnimation.ids = { 21, 22 };
	AnimationSystem::addAnimation(mWorld->player, tiledAnimation, Actions::Walk, Direction::Down);
	tiledAnimation.ids = { 27, 28 };
	AnimationSystem::addAnimation(mWorld->player, tiledAnimation, Actions::Walk, Direction::Right);
	tiledAnimation.ids = { 24, 25 };
	AnimationSystem::addAnimation(mWorld->player, tiledAnimation, Actions::Walk, Direction::Left);

	tiledAnimation.ids = { 17 };
	AnimationSystem::addAnimation(mWorld->player, tiledAnimation, Actions::Rotate, Direction::Up);
	tiledAnimation.ids = { 20 };
	AnimationSystem::addAnimation(mWorld->player, tiledAnimation, Actions::Rotate, Direction::Down);
	tiledAnimation.ids = { 26 };
	AnimationSystem::addAnimation(mWorld->player, tiledAnimation, Actions::Rotate, Direction::Right);
	tiledAnimation.ids = { 23 };
	AnimationSystem::addAnimation(mWorld->player, tiledAnimation, Actions::Rotate, Direction::Left);
	///Register and init entity to poolAnimationComponent



	///Init delayTransiction
	mWorld->delayTransictionToBattle.coolDown = mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[mWorld->player]].actionDelays[Actions::Walk].coolDown
		+ 0.5f;
	///Init delayTransiction
	
	
	
	///Init camera
	Camera camera = EntityManager::get().createEntity();
	mWorld->camera = camera;
	registerEntity(&mWorld->mPoolTransformComponent, camera);
	mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[camera]].pos
		=
		mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[mWorld->player]].pos;
	///Init camera



	///Init PhaseHandler
	mWorld->phaseHandler.addPhaseBack(PhaseType::Exploring, StatePhase::On);
	///Init PhaseHandler



	SDL_Log("Ended creation");



	//Init all system
	CameraSystem::init();

	AnimationSystem::init();

	EnemySystem::init();
	//Init all system
	///FOR TESTING
}



void Game::init()
{
	//Init principle reference to Game class
	Game::sGameInstance = this;
	//Init principle reference to Game class



	//Initialization of enviroment
	SDL_Log("STARTING INITIALIZATION:");
	if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER) )
	{
		SDL_Log("ERROR DURING SDL ENVIROMENT INITIALIZATION: %s", SDL_GetError());
		exit(1);
	}
	SDL_Log("\t-Succes initialization of SDL Enviroment");
	//Initialization of enviroment
	


	//Init other enviroment
	WindowHandler::get();

	TextureHandler::get();
	//Init other enviroment



	SDL_Log("\t-Initialization ended without problems");
	SDL_Log("");
}



void Game::startBattle()
{
	//Set the PhaseHandler
	mWorld->phaseHandler.addPhaseBack(PhaseType::Battle, StatePhase::On);
	mWorld->phaseHandler.setStatePhase(PhaseType::Exploring, StatePhase::Paused);
	//Set the PhaseHandler
}



void Game::calcDeltaTime()
{
	//Update deltaTime
	mDeltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	mTicksCount = static_cast<float>( SDL_GetTicks() );
	//Update deltaTime



	//Clamp value of deltaTime
	if (mDeltaTime > sMaxDeltaTime)
	{
		mDeltaTime = sMaxDeltaTime;
	}
	//Clamp value of deltaTime
}



void Game::sleep()
{
	if (mVsync)
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
}



void Game::shutdown()
{
	delete mWorld;
}



Game* Game::get()
{
	return sGameInstance;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class Game
//-----------------------------------------------------------------------------------------------------------------------------------------

//RUN METHOD
void run()
{
	Game* game = new Game();

	game->init();
	game->loadData();

	while (game->isRunning())
	{
		game->calcDeltaTime();
		game->processInput();
		game->update();
		game->generateOutput();
		game->sleep();
	}

	game->shutdown();
}
//RUN METHOD
#include "Game.h"

//Including Generals
#include "Direction.h"
//Including Generals

//Including Enviroment
#include "Enviroment/WindowHandler.h"
#include "Enviroment/TextureHandler.h"
//Including Enviroment

//Including Debugging Enviroment
#include "Debugging/DebugInfo.h"
//Including Debugging Enviroment

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
	MoveSystem::move();

	CameraSystem::updateCamera();

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
}



void Game::input()
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
		if (mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[mWorld->player]].currentAction == Actions::NoneActions)
		{
			mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[mWorld->player]].currentAction = Actions::WalkUp;
			MoveSystem::startMove(mWorld->player);
		}
	}
	else if (keyStates[SDL_SCANCODE_S])
	{
		if (mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[mWorld->player]].currentAction == Actions::NoneActions)
		{
			mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[mWorld->player]].currentAction = Actions::WalkDown;
			MoveSystem::startMove(mWorld->player);
		}
	}
	else if (keyStates[SDL_SCANCODE_D])
	{
		if (mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[mWorld->player]].currentAction == Actions::NoneActions)
		{
			mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[mWorld->player]].currentAction = Actions::WalkRight;
			MoveSystem::startMove(mWorld->player);
		}
	}
	else if (keyStates[SDL_SCANCODE_A])
	{
		if (mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[mWorld->player]].currentAction == Actions::NoneActions)
		{
			mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[mWorld->player]].currentAction = Actions::WalkLeft;
			MoveSystem::startMove(mWorld->player);
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
}



void Game::generateOutput()
{
	//Clean screen
	SDL_RenderClear(WindowHandler::get().getRenderer());
	//Clean screen



	//Prepare rendering
	RenderSystem::draw();
	//Prepare rendering



	//Render elements
	SDL_RenderPresent(WindowHandler::get().getRenderer());
	//Render elements
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

	for (int i = 0; i < 5; i++)
	{
		Entity e = EntityManager::get().createEntity();

		registerEntity(&mWorld->mPoolTransformComponent, e);
		mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[e]].pos = { x, x };
		mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[e]].tileOccupied = { (int)x, (int)x };
		mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[e]].z = 0;
		registerEntity(&mWorld->mPoolDrawComponent, e);
		mWorld->mPoolDrawComponent.mPackedArray[mWorld->mPoolDrawComponent.mReverseArray[e]].id = 10;

		x += 1.0f;
	}

	mWorld->player = 1;
	registerEntity(&mWorld->mPoolMoveComponent, mWorld->player);
	mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[mWorld->player]].pos = { 7.0f, 1.0f };
	mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[mWorld->player]].tileOccupied = 
		mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[mWorld->player]].pos;

	mWorld->mPoolMoveComponent.mPackedArray[mWorld->mPoolMoveComponent.mReverseArray[mWorld->player]].currentDirection = NoneDirection;
	mWorld->mPoolMoveComponent.mPackedArray[mWorld->mPoolMoveComponent.mReverseArray[mWorld->player]].lastDirection = NoneDirection;

	///Register and init entity to PoolActionComponent
	registerEntity(&mWorld->mPoolActionComponent, mWorld->player);
	
	mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[mWorld->player]].currentAction = NoneActions;
	
	///ADD WALK DELAY
	mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[mWorld->player]].actionDelays[Actions::WalkUp].coolDown = 0.5f;
	mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[mWorld->player]].actionDelays[Actions::WalkDown].coolDown = 0.5f;
	mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[mWorld->player]].actionDelays[Actions::WalkRight].coolDown = 0.5f;
	mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[mWorld->player]].actionDelays[Actions::WalkLeft].coolDown = 0.5f;	
	///ADD WALK DELAY

	///ADD ROTATE DELAY
	mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[mWorld->player]].actionDelays[Actions::RotateUp].coolDown = 0.2f;
	mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[mWorld->player]].actionDelays[Actions::RotateDown].coolDown = 0.2f;
	mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[mWorld->player]].actionDelays[Actions::RotateRight].coolDown = 0.2f;
	mWorld->mPoolActionComponent.mPackedArray[mWorld->mPoolActionComponent.mReverseArray[mWorld->player]].actionDelays[Actions::RotateLeft].coolDown = 0.2f;
	///ADD ROTATE DELAY

	///Register and init entity to PoolActionComponent

	///Init camera
	Camera camera = EntityManager::get().createEntity();
	mWorld->camera = camera;
	registerEntity(&mWorld->mPoolTransformComponent, camera);
	mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[camera]].pos 
		= 
	mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[mWorld->player]].pos;
	///Init camera



	SDL_Log("Ended creation");
	
	

	//Init all system
	CameraSystem::init();
	//Init all system
	///FOR TESTING
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
		game->input();
		game->update();
		game->generateOutput();
		game->sleep();
	}

	game->shutdown();
}
//RUN METHOD
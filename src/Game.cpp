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
//Including System

//Some Shit
#include "World.h"
//Some Shit





///ADD PRECOMPILED HEADERS
///ADD A PHASE HANDLER
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class Game
//-----------------------------------------------------------------------------------------------------------------------------------------
const float Game::sMaxDeltaTime = 0.5f;
Game* Game::sGameInstance = nullptr;





void Game::update()
{
	MoveSystem::move();
	CameraSystem::updateCamera();
}



void Game::input()
{
	SDL_Event event;

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
				break;
			}
			break;
		}
	}

	const Uint8* keyStates = SDL_GetKeyboardState(nullptr);

	if (keyStates[SDL_SCANCODE_1])
	{
		mWorld->cameraData.zoom += 0.1f;
	}
	if (keyStates[SDL_SCANCODE_2])
	{
		mWorld->cameraData.zoom -= 0.1f;
	}

	if (keyStates[SDL_SCANCODE_W])
	{
		mWorld->mPoolMoveComponent.mPackedArray[mWorld->mPoolMoveComponent.mReverseArray[mWorld->player]].currentDirection = Direction::Up;
	}
	else if (keyStates[SDL_SCANCODE_S])
	{
		mWorld->mPoolMoveComponent.mPackedArray[mWorld->mPoolMoveComponent.mReverseArray[mWorld->player]].currentDirection = Direction::Down;
	}
	else if (keyStates[SDL_SCANCODE_D])
	{
		mWorld->mPoolMoveComponent.mPackedArray[mWorld->mPoolMoveComponent.mReverseArray[mWorld->player]].currentDirection = Direction::Right;
	}
	else if (keyStates[SDL_SCANCODE_A])
	{
		mWorld->mPoolMoveComponent.mPackedArray[mWorld->mPoolMoveComponent.mReverseArray[mWorld->player]].currentDirection = Direction::Left;
	}
}



void Game::generateOutput()
{
	SDL_RenderClear(WindowHandler::get().getRenderer());

	RenderSystem::draw();

	SDL_RenderPresent(WindowHandler::get().getRenderer());
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

	float x = 0.0f;

	for (int i = 0; i < 5; i++)
	{
		Entity e = EntityManager::get().createEntity();

		registerEntity(&mWorld->mPoolTransformComponent, e);
		mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[e]].pos = { x, x };
		registerEntity(&mWorld->mPoolDrawComponent, e);
		mWorld->mPoolDrawComponent.mPackedArray[mWorld->mPoolDrawComponent.mReverseArray[e]].id = 10;

		x += 1.0f;
	}

	mWorld->player = 1;
	registerEntity(&mWorld->mPoolMoveComponent, mWorld->player);
	mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[mWorld->player]].pos = { 7.0f, 1.0f };

	mWorld->mPoolMoveComponent.mPackedArray[mWorld->mPoolMoveComponent.mReverseArray[mWorld->player]].currentDirection = NoneDirection;
	mWorld->mPoolMoveComponent.mPackedArray[mWorld->mPoolMoveComponent.mReverseArray[mWorld->player]].lastDirection = NoneDirection;

	Camera camera = EntityManager::get().createEntity();
	mWorld->camera = camera;
	registerEntity(&mWorld->mPoolTransformComponent, camera);
	mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[camera]].pos 
		= 
	mWorld->mPoolTransformComponent.mPackedArray[mWorld->mPoolTransformComponent.mReverseArray[mWorld->player]].pos;

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
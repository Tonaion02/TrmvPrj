#include "Game.h"

//Including Ecs
#include "ECS/ECS.h"
//Including Ecs

//Including some context
#include "World.h"
//Including some context

//Including System
#include "Systems/RenderSystem.h"
#include "Systems/MoveSystem.h"
#include "Systems/CameraSystem.h"
#include "Systems/ActionSystem.h"
#include "Systems/AnimationSystem.h"
#include "Systems/TileSystem.h"
#include "Systems/EnemySystem.h"

//Including Battle System
#include "Systems/Battle/BattleRenderSystem.h"
#include "Systems/Battle/BattleMoveSystem.h"
#include "Systems/Battle/ColliderSystem.h"
#include "Systems/Battle/BattleLifeSystem.h"
//Including Battle System
//Including System

//Including Enviroment
#include "Enviroment/WindowHandler.h"
#include "Enviroment/TextureHandler.h"
//Including Enviroment

//Including Some Utils
#include "Misc/Direction.h"
#include "Misc/Grid.h"

#include "utils/FromTypeToText.h"
//Including Some Utils



///FOR TESTING
#include "utils/StringAndFile/XMLvariab.h"

#include "Scenes/ExploringScene.h"
#include "Scenes/BattleScene.h"
#include "Scenes/GeneralMenuScene.h"

#include "utils/Physic/DataGridSP.h"
#include "utils/Physic/GridSP.h"

#include "Enviroment/Input/Input.h"
///FOR TESTING





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class Game
//-----------------------------------------------------------------------------------------------------------------------------------------
const float Game::sMaxDeltaTime = 0.5f;
Game* Game::sGameInstance = nullptr;





void Game::update()
{
	resetIteratorScene();

	while (!isEndedScenes())
	{
		BaseScene* current = currentScene();

		current->updateScene();

		nextScene();
	}
}



void Game::processInput()
{
	//General handling of the Input
	updateInput();



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



	//ProcessInput for each scene
	resetIteratorScene();

	while (!isEndedScenes())
	{
		BaseScene* current = currentScene();

		current->processInputScene();

		nextScene();
	}
	//ProcessInput for each scene

	//General handling of the Input
}



void Game::generateOutput()
{
	//Clean screen
	SDL_SetRenderDrawColor(WindowHandler::get().getRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(WindowHandler::get().getRenderer());
	//Clean screenw



	resetIteratorScene();

	while (!isEndedScenes())
	{
		BaseScene* current = currentScene();

		current->generateOutputScene();

		nextScene();
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

	mDebugMode = true;

	mDeltaTime = 0.0f;
	mTicksCount = 0.0f;
	//Init some base data



	//Init world
	world = new World();
	//Init world



	//Create Scenes
	sExploringScene = new ExploringScene();
	sExploringScene->loadScene();
	sBattleScene = new BattleScene();
	sBattleScene->loadScene();
	activateScene<ExploringScene>();
	sGeneralMenuScene = new GeneralMenuScene();
	sGeneralMenuScene->loadScene();
	//Create Scenes



	//Load TileSet and Texture
	int tileDim = 32;

	world->currentLevel.texture = TextureHandler::get().getTexture("data/buch-outdoor.png");
	world->mTileSetHandler.loadTileSet("data/buch-outdoor.png", tileDim);
	world->currentLevel.tileSet = world->mTileSetHandler.getTileSet("data/buch-outdoor.png");
	world->textureActor = TextureHandler::get().getTexture("data/player.png");
	world->mTileSetHandler.loadTileSet("data/player.png", tileDim);
	world->tilesetActor = world->mTileSetHandler.getTileSet("data/player.png");

	TextureHandler::get().loadTexture("data/brimstone.png");
	world->mTileSetHandler.loadTileSet("data/brimstone.png", tileDim);

	SDL_Log("Texture and TileSet loaded");
	//Load TileSet and Texture



	//Load base UniqueTile
	XMLvariab* chestTest = TileSystem::uniqueTileWrapper("data/chest.tx");
	sExploringScene->templatesUniqueTile["chest.tx"] = chestTest;
	//Load base UniqueTile


	//Load Level	
	world->currentLevel = levelWrapper("data/level0.tmx");
	
	SDL_Log("Level loaded");
	//Load Level



	///FOR TESTING

	//Init debugTimer
	world->debugInfoTimer.coolDown = 1.0f;
	initTimer(&world->debugInfoTimer);
	//Init debugTimer

	float x = 0.0f;
	short int z = 0;

	for (int i = 0; i < 5; i++)
	{
		Entity e = createEntityId();

		registerEntity(&world->mPoolTransformComponent, e);
		getCmpEntity(&world->mPoolTransformComponent, e)->pos = { x, x };
		getCmpEntity(&world->mPoolTransformComponent, e)->tileOccupied = { (int)x, (int)x };
		getCmpEntity(&world->mPoolTransformComponent, e)->z = z;
		registerEntity(&world->mPoolDrawComponent, e);
		getCmpEntity(&world->mPoolDrawComponent, e)->id = 17;

		//Register to the group of the level
		registerEntity(&world->currentLevel.groupsEntities[z], e);
		//Register to the group of the level

		if (e != 1)
		{
			TileSystem::registerPos({ (int)x,(int)x }, z, e);

			registerEntity(&world->mPoolMoveComponent, e);
			getCmpEntity(&world->mPoolMoveComponent, e)->currentDirection = NoneDirection;
			getCmpEntity(&world->mPoolMoveComponent, e)->lastDirection = Direction::Down;

			registerEntity(&world->mPoolActionComponent, e);
			getCmpEntity(&world->mPoolActionComponent, e)->currentAction = NoneActions;
			getCmpEntity(&world->mPoolActionComponent, e)->actionDelays[Actions::Walk].coolDown = 0.5f;
			getCmpEntity(&world->mPoolActionComponent, e)->actionDelays[Actions::Rotate].coolDown = 0.5f;
			getCmpEntity(&world->mPoolActionComponent, e)->actionDelays[Actions::Interact].coolDown = 0.5f;

			registerEntity(&world->mPoolAnimationComponent, e);
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
			registerEntity(&world->mPoolBaseEnemyComponent, e);

			std::vector<Direction> path;
			path.push_back(Direction::Right);
			path.push_back(Direction::Right);
			path.push_back(Direction::Down);
			path.push_back(Direction::Right);
			path.push_back(Direction::Right);
			path.push_back(Direction::Right);
			path.push_back(Direction::Down);
			path.push_back(Direction::Down);

			getCmpEntity(&world->mPoolBaseEnemyComponent, e)->path = path;
		}

		//if (e == 3)
		//{
		//	registerEntity(&world->mPoolBaseEnemyComponent, e);

		//	std::vector<Direction> path;
		//	path.push_back(Direction::Right);
		//	//path.push_back(Direction::Right);

		//	getCmpEntity(&world->mPoolBaseEnemyComponent, e)->path = path;



		//	//getCmpEntity(&world->mPoolTransformComponent, e)->pos = { 7, 7 };
		//	//getCmpEntity(&world->mPoolTransformComponent, e)->tileOccupied = { 7, 7 };
		//	//getCmpEntity(&world->mPoolTransformComponent, e)->z = 1;
		//}

		x += 1.0f;
	}



	world->player = 1;

	TileSystem::unRegisterPos(getCmpEntity(&world->mPoolTransformComponent, world->player)->tileOccupied, z);
	getCmpEntity(&world->mPoolTransformComponent, world->player)->pos = { 17.0f, 16.0f };
	getCmpEntity(&world->mPoolTransformComponent, world->player)->tileOccupied = static_cast<Vector2i>(getCmpEntity(&world->mPoolTransformComponent, world->player)->pos);
	TileSystem::registerPos(getCmpEntity(&world->mPoolTransformComponent, world->player)->tileOccupied, z, world->player);

	registerEntity(&world->mPoolMoveComponent, world->player);
	getCmpEntity(&world->mPoolMoveComponent, world->player)->currentDirection = Direction::NoneDirection;
	getCmpEntity(&world->mPoolMoveComponent, world->player)->lastDirection = Direction::Down;

	///Register and init entity to PoolActionComponent
	registerEntity(&world->mPoolActionComponent, world->player);

	getCmpEntity(&world->mPoolActionComponent, world->player)->currentAction = Actions::NoneActions;

	getCmpEntity(&world->mPoolActionComponent, world->player)->actionDelays[Actions::Walk].coolDown = 0.5f;
	getCmpEntity(&world->mPoolActionComponent, world->player)->actionDelays[Actions::Rotate].coolDown = 0.2f;
	getCmpEntity(&world->mPoolActionComponent, world->player)->actionDelays[Actions::Interact].coolDown = 0.5f;
	///Register and init entity to PoolActionComponent

	///Register and init entity to poolAnimationComponent
	registerEntity(&world->mPoolAnimationComponent, world->player);

 	TiledAnimation tiledAnimation;

	tiledAnimation.ids = { 17 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::NoneActions, Direction::Up);
	tiledAnimation.ids = { 20 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::NoneActions, Direction::Down);
	tiledAnimation.ids = { 26 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::NoneActions, Direction::Right);
	tiledAnimation.ids = { 23 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::NoneActions, Direction::Left);

	tiledAnimation.ids = { 18, 19 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::Walk, Direction::Up);
	tiledAnimation.ids = { 21, 22 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::Walk, Direction::Down);
	tiledAnimation.ids = { 27, 28 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::Walk, Direction::Right);
	tiledAnimation.ids = { 24, 25 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::Walk, Direction::Left);

	tiledAnimation.ids = { 17 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::Rotate, Direction::Up);
	tiledAnimation.ids = { 20 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::Rotate, Direction::Down);
	tiledAnimation.ids = { 26 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::Rotate, Direction::Right);
	tiledAnimation.ids = { 23 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::Rotate, Direction::Left);

	tiledAnimation.ids = { 85, 86, 87 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::Interact, Direction::Up);
	tiledAnimation.ids = { 88, 89, 90 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::Interact, Direction::Down);
	tiledAnimation.ids = { 94, 95, 96 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::Interact, Direction::Right);
	tiledAnimation.ids = { 91, 92, 93 };
	AnimationSystem::addAnimation(world->player, tiledAnimation, Actions::Interact, Direction::Left);
	///Register and init entity to poolAnimationComponent



	///Init delayTransiction
	world->delayTransictionToBattle.coolDown = getCmpEntity(&world->mPoolActionComponent, world->player)->actionDelays[Actions::Walk].coolDown + 0.5f;
	///Init delayTransiction
	
	
	
	///Init camera
	world->camera = createEntityId();
	///Init camera



	///Init test for Battle Phase
	int n = 4;
	bool first = true;
	Entity firstEntity;

	for (int i = 0; i < n; i++)
	{
		Entity e = createEntityId();

		if (first)
		{
			firstEntity = e;
			first = false;
		}

		registerEntity(&world->mPoolTransformBattleComponent, e);
		if (i == 0)
		{
			getCmpEntity(&world->mPoolTransformBattleComponent, e)->pos = { 80.0f, 1.0f };
			world->BattlePlayerEntity = e;
			registerEntity(&world->mPoolPlayerBattleComponent, e);

			world->delayFiring.coolDown = 0.5f;
			initTimer(&world->delayFiring);
			world->delayHitBox.coolDown = 0.05f;
			initTimer(&world->delayHitBox);
		}
		else
		{
			Vector2i pos = { random() % (world->currentLevel.battleCamp.dim.x * 16), random() % (world->currentLevel.battleCamp.dim.y * 16) };
			
			for (int j = 0, iteratorEntity = firstEntity; j < i; j++, iteratorEntity++)
			{
				TransformBattleComponent* transform = getCmpEntity(&world->mPoolTransformBattleComponent, iteratorEntity);
				if (ColliderSystem::detectCollision(pos, Vector2i(tileDim, tileDim), transform->pos, { tileDim, tileDim }))
				{
					pos = { random() % (world->currentLevel.battleCamp.dim.x * 16), random() % (world->currentLevel.battleCamp.dim.y * 16) };
					j = 0, iteratorEntity = firstEntity;
				}
			}
			
			getCmpEntity(&world->mPoolTransformBattleComponent, e)->pos = pos;
			registerEntity(&world->mPoolEnemyBattleComponent, e);
		}

		registerEntity(&world->mPoolControlledRectColliderComponent, e);

		registerEntity(&world->mPoolPhysicBoxComponent, e);
		getCmpEntity(&world->mPoolPhysicBoxComponent, e)->mass = 1.0f;
		getCmpEntity(&world->mPoolPhysicBoxComponent, e)->v = { 0.0f, 0.0f };
		
		registerEntity(&world->mPoolRectColliderComponent, e);
		getCmpEntity(&world->mPoolRectColliderComponent, e)->dim = { tileDim, tileDim };
		
		registerEntity(&world->mPoolDrawBattleComponent, e);
		getCmpEntity(&world->mPoolDrawBattleComponent, e)->id = 17;
		getCmpEntity(&world->mPoolDrawBattleComponent, e)->tileSet = world->mTileSetHandler.getTileSet("data/player.png");
		getCmpEntity(&world->mPoolDrawBattleComponent, e)->dim = getCmpEntity(&world->mPoolDrawBattleComponent, e)->tileSet->tileDim;

		registerEntity(&world->mPoolDamageComponent, e);

		registerEntity(&world->mPoolLifeBarComponent, e);
		getCmpEntity(&world->mPoolLifeBarComponent, e)->health = 300.0f;



		//register Entity to GridSP for collision detection
		registerEntity(e, world->currentLevel.battleCamp.gridSP);
		//register Entity to GridSP for collision detection
	}
	///Init test for Battle Phase



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



bool Game::isInBattle()
{
	return isActiveScene<BattleScene>();
}



void Game::startBattle()
{
	//Push up the BattleScene
	getScene<ExploringScene>()->setStatus(statusScene::PauseScene);
	activateScene<BattleScene>();
	//Push up the BattleScene



	//Set the CameraData for the camera
	world->backupExploringCameraData = world->cameraData;

	world->cameraData = world->backupBattleCameraData;
	//Set the CameraData for the camera
}



bool Game::isInGeneralMenu()
{
	return isActiveScene<GeneralMenuScene>();
}



void Game::startGeneralMenu()
{
	if (isActiveScene<BattleScene>())
	{
		getScene<BattleScene>()->setStatus(statusScene::PauseScene);
	}
	else if (isActiveScene<ExploringScene>())
	{
		getScene<ExploringScene>()->setStatus(statusScene::PauseScene);
	}
	activateScene<GeneralMenuScene>();
}



void Game::endGeneralMenu()
{
	getScene<GeneralMenuScene>()->setStatus(statusScene::PauseScene);
	deActivateScene<GeneralMenuScene>();
	if (sGeneralMenuScene->choice == 0)
	{
		getScene<ExploringScene>()->setStatus(statusScene::RunningScene);
	}
	else if (sGeneralMenuScene->choice == 1)
	{
		getScene<BattleScene>()->setStatus(statusScene::RunningScene);
	}
	sGeneralMenuScene->choice = -1;
}



void Game::calcDeltaTime()
{
	//Update deltaTime
	mDeltaTime = ( SDL_GetTicks()  - mTicksCount) / 1000.0f;
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
	delete world;
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
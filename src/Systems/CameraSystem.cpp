#include "Systems/CameraSystem.h"

//Including some context
#include "Game.h"
#include "World.h"
//Including some context

#include "Data/Phase/Phase.h"

//Including enviroment
#include "Enviroment/WindowHandler.h"
//Including enviroment

#include "Data/Camera/Camera.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class CameraSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
void CameraSystem::init()
{
	//Init some base info about Camera
	World* world = Game::get()->getWorld();

	world->cameraData.adj = { 0, 0 };
	world->cameraData.nTileToRender = { 30, 30 };
	world->cameraData.baseScale = 1.0f;

	Vector2i screenDim = WindowHandler::get().getWindowDimension();
	Vector2i outputDim = world->currentLevel.tileSet.tileDim * world->cameraData.nTileToRender;
	//Init some base info about Camera

	//Set baseScale based on screen size
	world->cameraData.baseScale = std::max(screenDim.x / (float)outputDim.x, screenDim.y / (float)outputDim.y);
	//Set baseScale based on screen size
	
	//Calculate clamp value for scale
	int maxVisibleSpaceDim = std::max(screenDim.x, screenDim.y);
	world->cameraData.maxZoom = (maxVisibleSpaceDim / 2.0f) * tanf(ToRadians(30.0f));
	int minVisibleSpaceDim = static_cast<int>( (5 * world->currentLevel.tileSet.tileDim.x * world->cameraData.baseScale) );
	world->cameraData.minZoom = (minVisibleSpaceDim / 2.0f) * tanf(ToRadians(30.0f));
	world->cameraData.zoom = world->cameraData.maxZoom;
	//Calculate clamp value for scale

	//Calculate scaleZoom and add to the baseScale
	float visibleSpaceDim = 2 * tanf(ToRadians(60.0f)) * world->cameraData.zoom;
	Vector2f scaleZoom = { screenDim.x / (float)visibleSpaceDim, screenDim.y / (float)visibleSpaceDim };
	world->cameraData.baseScale *= std::max(scaleZoom.x, scaleZoom.y);
	//Calculate scaleZoom and add to the baseScale

	//Init the backup of the CameraData
	world->backupBattleCameraData = world->cameraData;
	world->backupExploringCameraData = world->cameraData;
	//Init the backup of the CameraData
}



void CameraSystem::updateCamera(const Vector2f& newPos)
{
	World* world = Game::get()->getWorld();

	//Update position of Camera (following the player)
	//world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[world->camera]].pos
	//	=
	//	world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[world->player]].pos;
	world->cameraData.pos = newPos;
	//Update position of Camera (following the player)



	//Take base info about
	Vector2i screenDim = WindowHandler::get().getWindowDimension();
	//Vector2f pos = world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[world->player]].pos;
	Vector2f pos = world->cameraData.pos;
	//Take base info about



	//Calculate startToRender and endToRender tile

	//Dividere per lunghezza tile la posizione se si è in battaglia
	Vector2i scaledTileDim = (Vector2f)world->currentLevel.tileSet.tileDim * world->cameraData.baseScale;
	Vector2f realScaledImageDim = world->currentLevel.dim * scaledTileDim;

	if (Game::get()->isInBattle() )
	{
		pos.x = pos.x / static_cast<float>( world->currentLevel.tileSet.tileDim.x );
		pos.y = pos.y / static_cast<float>( world->currentLevel.tileSet.tileDim.y );
	}


	world->cameraData.startToRender = { (int)pos.x - world->cameraData.nTileToRender.x / 2,(int)pos.y - world->cameraData.nTileToRender.y / 2 };
	world->cameraData.endToRender = { (int)pos.x + world->cameraData.nTileToRender.x / 2 + 2,(int)pos.y + world->cameraData.nTileToRender.y / 2 + 2 };

	if (world->cameraData.startToRender.x < 0)
	{
		world->cameraData.startToRender.x = 0;
		world->cameraData.endToRender.x = world->cameraData.nTileToRender.x +1;
	}
	else if (world->cameraData.endToRender.x >= world->currentLevel.dim.x)
	{
		world->cameraData.startToRender.x = world->currentLevel.dim.x - world->cameraData.nTileToRender.x -1;
		world->cameraData.endToRender.x = world->currentLevel.dim.x;
	}
		
	if (world->cameraData.startToRender.y < 0)
	{
		world->cameraData.startToRender.y = 0;
		world->cameraData.endToRender.y = world->cameraData.nTileToRender.y +1;
	}
	else if (world->cameraData.endToRender.y >= world->currentLevel.dim.y)
	{
		world->cameraData.startToRender.y = world->currentLevel.dim.y - world->cameraData.nTileToRender.y -1;
		world->cameraData.endToRender.y = world->currentLevel.dim.y;
	}
	//Calculate startToRender and endToRender tile



	//Calculate adj of the screen
	//Vector2i scaledTileDim = (Vector2f)world->currentLevel.tileSet.tileDim * world->cameraData.baseScale;
	//Vector2f realScaledImageDim = world->currentLevel.dim * scaledTileDim;
	pos = pos * scaledTileDim + scaledTileDim;


	if (pos.x - screenDim.x / 2.0f < 0.0f)
	{
		world->cameraData.adj.x = 0;
	}
	else if (pos.x + screenDim.x / 2.0f >= world->currentLevel.dim.x * scaledTileDim.x)
	{
		world->cameraData.adj.x = static_cast<int>(screenDim.x - realScaledImageDim.x);
	}
	else
	{
		world->cameraData.adj.x = -(static_cast<int>(pos.x) - screenDim.x / 2);
	}

	if (pos.y - screenDim.y / 2.0f < 0.0f)
	{
		world->cameraData.adj.y = 0;
	}
	else if (pos.y + screenDim.y / 2.0f >= world->currentLevel.dim.y * scaledTileDim.y)
	{
		world->cameraData.adj.y = static_cast<int>(screenDim.y - realScaledImageDim.y);
	}
	else
	{
		world->cameraData.adj.y = -(static_cast<int>(pos.y) - screenDim.y / 2);
	}
	//Calculate adj of the screen
}



void CameraSystem::onUpdateWindowSize()
{
	//Take base info
	World* world = Game::get()->getWorld();
	Vector2i screenDim = WindowHandler::get().getWindowDimension();
	Vector2i outputDim = world->currentLevel.tileSet.tileDim * world->cameraData.nTileToRender;
	//Take base info

	//Set baseScale
	world->cameraData.baseScale = std::max(screenDim.x / (float)outputDim.x, screenDim.y / (float)outputDim.y);
	//Set baseScale

	//Calculate clamp value of Camera
	int maxVisibleSpaceDim = std::max(screenDim.x, screenDim.y);
	int minVisibleSpaceDim = static_cast<int>((5 * world->currentLevel.tileSet.tileDim.x * world->cameraData.baseScale));
	world->cameraData.minZoom = (minVisibleSpaceDim / 2.0f) * tanf(ToRadians(30.0f));
	world->cameraData.maxZoom = (maxVisibleSpaceDim / 2.0f) * tanf(ToRadians(30.0f));
	world->cameraData.zoom = world->cameraData.maxZoom;
	//Calculate clamp value of Camera	

	//Calculate scaleZoom and add to the baseScale
	float visibleSpaceDim = 2 * tanf(ToRadians(60.0f)) * world->cameraData.zoom;
	Vector2f scaleZoom = { screenDim.x / (float)visibleSpaceDim, screenDim.y / (float)visibleSpaceDim };
	world->cameraData.baseScale *= std::max(scaleZoom.x, scaleZoom.y);
	//Calculate scaleZoom and add to the baseScale
}



void CameraSystem::updateCameraZoom(float sign)
{
	World* world = Game::get()->getWorld();

	//Update zoom value
	world->cameraData.zoom += sign * 0.1f * Game::get()->getDeltaTime() * 1000.0f;
	//Update zoom value



	//Clamp zoom value
	if (world->cameraData.zoom > world->cameraData.maxZoom)
		world->cameraData.zoom = world->cameraData.maxZoom;

	if (world->cameraData.zoom < world->cameraData.minZoom)
		world->cameraData.zoom = world->cameraData.minZoom;
	//Clamp zoom value



	CameraSystem::onUpdateZoom();
}



void CameraSystem::onUpdateZoom()
{
	//Take base info
	World* world = Game::get()->getWorld();
	Vector2i screenDim = WindowHandler::get().getWindowDimension();
	Vector2i outputDim = world->currentLevel.tileSet.tileDim * world->cameraData.nTileToRender;
	//Take base info

	//Set baseScale
	world->cameraData.baseScale = std::max(screenDim.x / (float)outputDim.x, screenDim.y / (float)outputDim.y);
	//Set baseScale

	//Calculate scaleZoom and add to the baseScale
	float visibleSpaceDim = 2 * tanf(ToRadians(60.0f)) * world->cameraData.zoom;
	Vector2f scaleZoom = { screenDim.x / (float)visibleSpaceDim, screenDim.y / (float)visibleSpaceDim };
	world->cameraData.baseScale *= std::max(scaleZoom.x, scaleZoom.y);
	//Calculate scaleZoom and add to the baseScale
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class CameraSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
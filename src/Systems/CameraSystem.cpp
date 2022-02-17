#include "Game.h"

#include "World.h"

//Including enviroment
#include "Enviroment/WindowHandler.h"
//Including enviroment

#include "Data/Camera/Camera.h"

#include "Systems/CameraSystem.h"





void CameraSystem::init()
{
	World* world = Game::get()->getWorld();

	//Init base info about camera
	world->cameraData.adj = { 0, 0 };
	world->cameraData.nTileToRender = { 20, 20 };
	world->cameraData.baseScale = 1.0f;

	CameraSystem::resetBaseInfo();
	//Init base info about camera
}



void CameraSystem::updateCamera()
{
	World* world = Game::get()->getWorld();

	//Update position of Camera
	world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[world->camera]].pos
		=
		world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[world->player]].pos;
	//Update position of Camera

	//Take base info about
	Vector2i screenDim = WindowHandler::get().getWindowDimension();
	Vector2f pos = world->mPoolTransformComponent.mPackedArray[world->mPoolTransformComponent.mReverseArray[world->player]].pos;
	//Take base info about

	//Calculate startToRender and endToRender tile
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
	Vector2i scaledTileDim = (Vector2f)world->currentLevel.tileSet.tileDim * world->cameraData.baseScale;
	Vector2f realScaledImageDim = world->currentLevel.dim * scaledTileDim;
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



void CameraSystem::resetBaseInfo()
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
	world->cameraData.maxZoom = (maxVisibleSpaceDim / 2.0f) * tan30;
	world->cameraData.minZoom = (5 * world->currentLevel.tileSet.tileDim.x) * tan30;
	world->cameraData.zoom = world->cameraData.maxZoom;
	//Calculate clamp value of Camera	
	
	//Calculate scaleZoom and add to the baseScale
	float visibleSpaceDim = 2 * tan60 * world->cameraData.zoom;
	Vector2f scaleZoom = { screenDim.x / (float)visibleSpaceDim, screenDim.y / (float)visibleSpaceDim };
	world->cameraData.baseScale *= std::max(scaleZoom.x, scaleZoom.y);
	//Calculate scaleZoom and add to the baseScale
}
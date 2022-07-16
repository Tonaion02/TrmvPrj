#include "Game.h"

#include "SDL_Enviroment.h"

#include "ECS/SceneManager.h"
#include "ECS/Scene.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class Scene
//-----------------------------------------------------------------------------------------------------------------------------------------
BaseScene::BaseScene(unsigned int typeScene)
	:game(Game::get()), world(Game::get()->getWorld()), status(statusScene::RunningScene)
{
	SceneManager::get().addScene(typeScene, this);
}



void BaseScene::setStatus(statusScene status)
{
	this->status = status;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class Scene
//-----------------------------------------------------------------------------------------------------------------------------------------
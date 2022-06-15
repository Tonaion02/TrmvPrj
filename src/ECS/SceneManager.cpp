#include "ECS/SceneManager.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class SceneManager
//-----------------------------------------------------------------------------------------------------------------------------------------
SceneManager::SceneManager()
	:currentScene(0)
{

}



void SceneManager::addScene(const std::string& nameScene, BaseScene* newScene)
{
	scenes[nameScene] = newScene;
}



void SceneManager::activateScene(const std::string& nameScene)
{
	//Controllo se è gia presente la scene

	activeScenes.emplace(activeScenes.begin(), scenes[nameScene]);
}



void SceneManager::deactivateScene(const std::string& nameScene)
{
	activeScenes.erase(std::find(activeScenes.begin(), activeScenes.end(), scenes[nameScene]));
}



BaseScene* SceneManager::getCurrentScene()
{
	return activeScenes[currentScene];
}



void SceneManager::nextScene()
{
	currentScene++;
}



void SceneManager::resetIterator()
{
	currentScene = 0;
}



bool SceneManager::isEndedScenes()
{
	return currentScene == activeScenes.size();
}



bool SceneManager::isActive(BaseScene* scene)
{
	//ASSERT: Controll if the scenes is in the list

	auto f = std::find(activeScenes.begin(), activeScenes.end(), scene);

	if (f != activeScenes.end())
		return true;

	return false;
}



BaseScene* SceneManager::getScene(const std::string& nameScene)
{
	//ASSERT: Controll if the scenes is in the list

	return scenes[nameScene];
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class SceneManager
//-----------------------------------------------------------------------------------------------------------------------------------------
#pragma once

#include <string>
#include <vector>
#include <map>





//ADD A MAX TO SCENES
class SceneManager
{
public:
	static SceneManager& get()
	{
		static SceneManager instance;
		return instance;
	}

	void addScene(unsigned int typeScene, class BaseScene* newScene);
	void activateScene(unsigned int typeScene);
	void deActivateScene(unsigned int typeScene);

	class BaseScene* getCurrentScene();
	void nextScene();
	void resetIterator();
	bool isEndedScenes();

	bool isActive(unsigned int typeScene);
	class BaseScene* getScene(unsigned int typeScene);

protected:
	SceneManager();

protected:
	std::map<unsigned int, class BaseScene*> scenes;
	std::vector<class BaseScene*> activeScenes;
	unsigned int currentScene;
};
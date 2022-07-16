#pragma once

#include "ECS/GroupEntity.h"






enum statusScene
{
	NoneStatusScene = -1,
	RunningScene,
	PauseScene
};



class BaseScene
{
public:
	BaseScene(unsigned int typeScene);

	virtual void loadScene() {}
	virtual void unLoadScene() {}
	virtual void activateScene() {}
	virtual void deActivateScene() {}
	virtual void updateScene() {}
	virtual void generateOutputScene() {}
	virtual void processInputScene() {}
	virtual void saveScene() {}

	void setStatus(statusScene status);

	inline class Game* getGame() { return game; }
	inline struct World* getWorld() { return world; }

protected:
	class Game* game;
	struct World* world;
	statusScene status;
};
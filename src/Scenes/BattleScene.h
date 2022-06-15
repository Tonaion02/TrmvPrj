#pragma once

#include "ECS/Scene.h"





class BattleScene : public BaseScene
{
public:
	explicit BattleScene();

	void updateScene() override;
	void generateOutputScene() override;
	void processInputScene() override;

protected:

public:

};
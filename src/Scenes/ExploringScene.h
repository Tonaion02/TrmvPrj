#pragma once

#include "ECS/Scene.h"





class ExploringScene : public BaseScene
{
public:
	explicit ExploringScene();

	void loadScene() override;
	void updateScene() override;
	void generateOutputScene() override;
	void processInputScene() override;

protected:
	class DrawableWidget* widget;
	bool showMenu;

public:
};
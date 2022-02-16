#pragma once

#include "ECS/System.h"





class RenderSystem : public System
{
public:
	static void draw();

protected:
	static void drawFirstLayerTileMap();
	static void drawOtherLayerTileMap();
};
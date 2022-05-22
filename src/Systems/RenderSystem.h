#pragma once





class RenderSystem
{
public:
	static void draw();

protected:
	static void drawFirstLayerTileMap();
	static void drawOtherLayerTileMap();
};
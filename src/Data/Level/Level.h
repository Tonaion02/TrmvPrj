#pragma once

#include "Math/Math.h"

#include "Enviroment/TileSet.h"

#include "GraphicTileLayer.h"
#include "Data/Level/TileMap.h"





struct Level
{
	GraphicTileLayer graphicTileLayer;
	TileMap tileMap;
	struct SDL_Texture* texture;
	TileSet tileSet;
	Vector2i dim;
	int maxZ;
};



Level levelWrapper(const std::string& path);
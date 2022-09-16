#pragma once

#include "ECS/GroupEntity.h"

#include "utils/Math/Math.h"

#include "Enviroment/TileSet.h"

#include "GraphicTileLayer.h"

#include "Data/Level/BattleCamp.h"

#include "Data/Level/TileMap.h"





struct Level
{
	GraphicTileLayer<MAX_W_MAP * MAX_H_MAP * MAX_Z_MAP> graphicTileLayer;
	TileMap tileMap;
	struct SDL_Texture* texture;
	TileSet* tileSet;
	Vector2i dim;
	int maxZ;

	BattleCamp battleCamp;

	std::vector<GroupEntity<>> groupsEntities;
};



Level levelWrapper(const std::string& path);
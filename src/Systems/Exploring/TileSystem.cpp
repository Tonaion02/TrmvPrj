#include "TileSystem.h"

//Including some Systems
#include "Systems/TileSystem.h"
//Including some Systems

//Including some Data info
#include "Data/Level/UniqueTile.h"
#include "Data/Level/ChestTile.h"
//Including some Data info

//Including Utils
#include "utils/Math/Math.h"

#include "utils/StringAndFile/XMLvariab.h"
#include "utils/StringAndFile/MyString.h"
//Including Utils

//Including world
#include "Game.h"
#include "World.h"
//Including world





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class TileSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
bool TileSystem::isWalkable(const Vector2i& pos, short int z)
{
	World* world = Game::get()->getWorld();

	switch (world->currentLevel.tileMap.tiles[z * world->currentLevel.dim.x * world->currentLevel.dim.y + 
											  pos.y * world->currentLevel.dim.x + 
									          pos.x].logicType)
	{
	case Wall:
	case Sea:
	case Chest:
		return false;
	}

	return true;
}



bool TileSystem::isInteractable(const Vector2i& pos, short int z)
{
	World* world = Game::get()->getWorld();

	switch (world->currentLevel.tileMap.tiles[z * world->currentLevel.dim.x * world->currentLevel.dim.y +
		                                      pos.y * world->currentLevel.dim.x +
		                                      pos.x].logicType)
	{
	case Wall:
	case Ground:
	case Sea:
		return false;

	case Chest:
		{
			ChestTile* chestTile = static_cast<ChestTile*>(world->currentLevel.tileMap.uniqueTiles[z * world->currentLevel.dim.x * world->currentLevel.dim.y +
				pos.y * world->currentLevel.dim.x +
				pos.x]);

			return !chestTile->isOpened;
		}
	}

	return true;
}



void TileSystem::registerPos(const Vector2i& pos, short int z, Entity e)
{
	World* world = Game::get()->getWorld();
	Level* currentLevel = &world->currentLevel;

	//DA SOSTITUIRE
	if (e != world->player)
	{
		currentLevel->tileMap.mappedEntities[currentLevel->dim.y * currentLevel->dim.x * z + currentLevel->dim.x * pos.y + pos.x] = EntityOccupier::EnemyOccupier;
	}
	else
	{
		currentLevel->tileMap.mappedEntities[currentLevel->dim.y * currentLevel->dim.x * z + currentLevel->dim.x * pos.y + pos.x] = EntityOccupier::PlayerOccupier;
	}
}



void TileSystem::unRegisterPos(const Vector2i& pos, short int z)
{
	World* world = Game::get()->getWorld();
	Level* currentLevel = &world->currentLevel;

	currentLevel->tileMap.mappedEntities[currentLevel->dim.y * currentLevel->dim.x * z + currentLevel->dim.x * pos.y + pos.x] = NoneEntityOccupier;
}



bool TileSystem::isOccupied(const Vector2i& pos, short int z)
{
	World* world = Game::get()->getWorld();
	Level* currentLevel = &world->currentLevel;

	return currentLevel->tileMap.mappedEntities[currentLevel->dim.y * currentLevel->dim.x * z + currentLevel->dim.x * pos.y + pos.x] != NoneEntityOccupier;
}



void TileSystem::interactReaction(const Vector2i& pos, short int z)
{
	World* world = Game::get()->getWorld();
	Level* currentLevel = &world->currentLevel;


	//Retrieve the logicType of the tile 
	LogicType logicType = static_cast<LogicType>(currentLevel->tileMap.tiles[z * world->currentLevel.dim.x * world->currentLevel.dim.y +
		pos.y * world->currentLevel.dim.x +
		pos.x].logicType);
	//Retrieve the logicType of the tile 

	//In case is a ChestTile
	if (logicType == LogicType::Chest)
	{
		//Retrieve and cast the chestTile
		ChestTile* chestTile = static_cast<ChestTile*>(currentLevel->tileMap.uniqueTiles[z * currentLevel->dim.x * currentLevel->dim.y + pos.y * currentLevel->dim.x + pos.x]);
		//Retrieve and cast the chestTile

		//Set isOpened value to true
		chestTile->isOpened = true;
		//Set isOpened value to true

		//Calculate how much graphic tiles we must skip
		int deep = 0;

		for (int z2 = 0; z2 < z; z2++)
			deep += currentLevel->graphicTileLayer.deepOfLayer[z2];

		int skip = deep * currentLevel->dim.x * currentLevel->dim.y + chestTile->internalLayer * currentLevel->dim.y * currentLevel->dim.x;
		//Calculate how much graphic tiles we must skip

		//Calculate the effective index of the graphic tiles to modify
		int index = skip + pos.y * currentLevel->dim.x + pos.x;
		//Calculate the effective index of the graphic tiles to modify
		
		//Modify the id of graphic tile
		currentLevel->graphicTileLayer.gTiles[index] = chestTile->idImages[static_cast<int>(chestTile->isOpened)];
		//Modify the id of graphic tile

		//Add the items of loot of the chest to inventory
		SDL_Log("Added item to invetory with id: %d", chestTile->idItem);
		//Add the items of loot of the chest to inventory
	}
	//In case is a ChestTile
}



XMLvariab* TileSystem::uniqueTileWrapper(const std::string& path)
{
	XMLvariab* var = new XMLvariab();

	std::vector<std::string> lines = getLines(path);

	//Delete first three lines
	lines.erase(lines.begin());
	lines.erase(lines.begin());
	lines.erase(lines.begin());
	//Delete first three lines

	//Delete last line
	lines.pop_back();
	//Delete last line

	//Transform the lines of objects in XMLvariable
	std::vector<XMLvariab> appoggio = getXMLvariables(lines);
	XMLvariab* object = &appoggio[0];
	//Transform the lines of objects in XMLvariable

	//Take gid from object and create corrispondent value
	var->createValue("gid", object->getValue("gid"));
	//Take gid from object and create corrispondent value

	//Delete "properties" line
	object->rawData.erase(object->rawData.begin());
	object->rawData.pop_back();
	//Delete "properties" line

	//Take properties of UniqueTile
	std::vector<XMLvariab> properties = getXMLvariables(object->rawData);
	//Take properties of UniqueTile

	//Create values from properties
	for (auto prop : properties)
		var->createValue(prop.getValue("name"), prop.getValue("value"));
	//Create values from properties

	return var;
}



UniqueTile* TileSystem::createUniqueTile(XMLvariab* tileInfo)
{
	//Get the logicType of the Tile
	LogicType logicType = static_cast<LogicType>(std::stoi(tileInfo->getValue("gid")) - 1);
	//Get the logicType of the Tile

	//Call the correct constructor thanks the logicType
	switch (logicType)
	{
	case Chest:
		return new ChestTile(*tileInfo);
		break;
	
	default:
		//In case we call this method for a non-UniqueTile
		__debugbreak();
		//In case we call this method for a non-UniqueTile
		break;
	}
	//Call the correct constructor thanks the logicType



	//Default return-value(to shut-up the compiler)
	return nullptr;
	//Default return-value(to shut-up the compiler)
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class TileSystem
//-----------------------------------------------------------------------------------------------------------------------------------------
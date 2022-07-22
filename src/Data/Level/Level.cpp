//Including stuff about level
#include "Data/Level/GraphicTileLayer.h"
#include "Data/Level/Level.h"
//Including stuff about level

//Including some context
#include "Game.h"
#include "World.h"
//Including some context

//Including Enviroment
#include "Enviroment/TextureHandler.h"
//Including Enviroment

//Including some file for formatting of strings and files
#include "utils/StringAndFile/MyString.h"
#include "utils/StringAndFile/XMLvariab.h"
//Including some file for formatting of strings and files

//Including some physics Data Structures
#include "utils/Physic/GridSP.h"
//Including some physics Data Structures





//-----------------------------------------------------------------------------------------------------------------------------------------
//Struct Level
//-----------------------------------------------------------------------------------------------------------------------------------------
Level levelWrapper(const std::string& path)
{
	World* world = Game::get()->getWorld();
	std::string baseDataPath = "data/";

	Level level;

	std::vector<std::string> lines = getLines(path);

	std::vector<XMLvariab> xmlVariables = getXMLvariables(lines);
	XMLvariab principle = xmlVariables[0];

	Vector2i levelDim;
	levelDim.x = stoi(principle.getValue("width"));
	levelDim.y = stoi(principle.getValue("height"));
	level.dim = levelDim;

	unsigned int tileDim = stoi(principle.getValue("tilewidth"));

	xmlVariables = getXMLvariables(principle.rawData);

	Vector2i posG = { 0, 0 };
	int zG = 0;

	Vector2i posT = { 0, 0 };
	int zT = 0;

	int firstGId;

	for (unsigned int i = 0; i < xmlVariables.size(); i++)
	{
		XMLvariab var = xmlVariables[i];

		//Analyze the xml variables
		if (var.name == "tileset")
		{		
			std::string path = var.getValue("source");
			path = baseDataPath + path.substr(0, path.find(".")) + ".png";

			if (path != "data/tekTileSet.png")
				level.tileSet = world->mTileSetHandler.getTileSet(path);
			else
				firstGId = std::stoi(var.getValue("firstgid"));
		}
		else if (var.name == "layer")
		{
			XMLvariab var2 = getXMLvariables(var.rawData)[0];

			for (unsigned int j = 0; j < var2.rawData.size(); j++)
			{
				std::string line = var2.rawData[j];
				std::vector<std::string> splittedLine = split(line, ",");

				for (auto stringValue : splittedLine)
				{
					level.graphicTileLayer.gTiles[zG * levelDim.x * levelDim.y + posG.y * levelDim.x + posG.x] = stoi(stringValue) - 1;

					posG.x++;
					if (posG.x == levelDim.x)
					{
						posG.y++;
						posG.x = 0;
					}
				}
			}

			zG++;
			posG.x = 0;
			posG.y = 0;
		}
		else if (var.name == "objectgroup")
		{
			//Distinguish from name beetween entity layer and tecnical layer


			//Set all the tiles to Ground
			level.tileMap.tiles.resize(levelDim.x * levelDim.y * (zT + 1));

			for (posT.y = 0; posT.y < levelDim.y; posT.y++)
			{
				for (posT.x = 0; posT.x < levelDim.x; posT.x++)
				{
					level.tileMap.tiles[zT * levelDim.y * levelDim.x + posT.y * levelDim.x + posT.x].logicType = static_cast<short int>(LogicType::Ground);
				}
			}
			//Set all the tiles to Ground



			//Set all the tiles to unOccupied
			level.tileMap.mappedEntities.resize(levelDim.x * levelDim.y * (zT + 1));

			for (posT.y = 0; posT.y < levelDim.y; posT.y++)
			{
				for (posT.x = 0; posT.x < levelDim.x; posT.x++)
				{
					level.tileMap.mappedEntities[zT * levelDim.y * levelDim.x + posT.y * levelDim.x + posT.x] = static_cast<int>(EntityOccupier::NoneEntityOccupier);
				}
			}
			//Set all the tiles to unOccupied



			//Add particular object to this layer
			if (var.withRawData)
			{
				std::vector<XMLvariab> variables = getXMLvariables(var.rawData);
				for (auto iter : variables)
				{
					Vector2i pos = { std::stoi(iter.getValue("x")), std::stoi(iter.getValue("y")) - world->currentLevel.tileSet->tileDim.y };
					pos = pos / world->currentLevel.tileSet->tileDim;
					int logicType = std::stoi(iter.getValue("gid")) - firstGId;
					level.tileMap.tiles[zT * levelDim.y * levelDim.x + pos.y * levelDim.x + pos.x].logicType = static_cast<int>(logicType);
				}
			}
			//Add particular object to this layer



			zT++;
		}
		//Analyze the xml variables
	}

	level.maxZ = zT;





	//Create the battleCamp
	level.battleCamp.dim = { 20, 20 };
	level.battleCamp.maxZ = 2;

	level.battleCamp.tileSet = *world->mTileSetHandler.getTileSet("data/buch-outdoor.png");

	for (int z = 0; z < level.battleCamp.maxZ; z++)
	{
		for (int y = 0; y < level.battleCamp.dim.y; y++)
		{
			for (int x = 0; x < level.battleCamp.dim.x; x++)
			{
				level.battleCamp.graphicTileLayer.gTiles[z * level.battleCamp.dim.x * level.battleCamp.dim.y + y * level.battleCamp.dim.x + x] = 13;
			}
		}
	}



	//Initialize the bound of the BattleCamp
	//Top
	level.battleCamp.boundCamp[0].start.x = 0;
	level.battleCamp.boundCamp[0].end.x = level.battleCamp.dim.x * level.battleCamp.tileSet.tileDim.x;
	level.battleCamp.boundCamp[0].start.y = (level.battleCamp.boundCamp[0].end.y = 0);
	level.battleCamp.boundCamp[0].orientation = 0;
	//Bottom
	level.battleCamp.boundCamp[1].start.x = 0;
	level.battleCamp.boundCamp[1].end.x = level.battleCamp.dim.x * level.battleCamp.tileSet.tileDim.x;
	level.battleCamp.boundCamp[1].start.y = (level.battleCamp.boundCamp[1].end.y = level.battleCamp.dim.y * level.battleCamp.tileSet.tileDim.y);
	level.battleCamp.boundCamp[1].orientation = 0;
	//Left
	level.battleCamp.boundCamp[2].start.x = (level.battleCamp.boundCamp[2].end.x = 0);
	level.battleCamp.boundCamp[2].start.y = 0;
	level.battleCamp.boundCamp[2].end.y = level.battleCamp.dim.y * level.battleCamp.tileSet.tileDim.y;
	level.battleCamp.boundCamp[2].orientation = 1;
	//Right
	level.battleCamp.boundCamp[3].start.x = (level.battleCamp.boundCamp[3].end.x = level.battleCamp.dim.x * level.battleCamp.tileSet.tileDim.x);
	level.battleCamp.boundCamp[3].start.y = 0;
	level.battleCamp.boundCamp[3].end.y = level.battleCamp.dim.y * level.battleCamp.tileSet.tileDim.y;
	level.battleCamp.boundCamp[3].orientation = 1;
	//Initialize the bound of the BattleCamp



	//Initialize the grid for spatial partition
	level.battleCamp.gridSP = GridSP(Vector2i(level.battleCamp.dim.x * level.tileSet->tileDim.x, level.battleCamp.dim.y * level.tileSet->tileDim.y),
		Vector2i(3 * level.tileSet->tileDim.x, 3 * level.tileSet->tileDim.y));
	//Initialize the grid for spatial partition

	//Create the battleCamp



	return level;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Struct Level
//-----------------------------------------------------------------------------------------------------------------------------------------
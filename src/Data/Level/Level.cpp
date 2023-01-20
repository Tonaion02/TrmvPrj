//Including stuff about level
#include "Data/Level/GraphicTileLayer.h"
#include "Data/Level/Level.h"
//Including stuff about level

//Including some context
#include "Game.h"
#include "World.h"
//Including some context

//Including scenes
#include "Scenes/ExploringScene.h"
//Including scenes

//Including some Systems
#include "Systems/Exploring/TileSystem.h"
//Including some Systems

//Including Enviroment
#include "Enviroment/TextureHandler.h"
//Including Enviroment

//Including some file for formatting of strings and files
#include "utils/StringAndFile/MyString.h"
#include "utils/StringAndFile/XMLvariab.h"
//Including some file for formatting of strings and files

//Including some physics Data Structures
#include "utils/Physic/GridSP.h"

#include "utils/Math/Vector2i.h"
//Including some physics Data Structures





//-----------------------------------------------------------------------------------------------------------------------------------------
//Struct Level
//-----------------------------------------------------------------------------------------------------------------------------------------
Level levelWrapper(const std::string& path)
{
	World* world = Game::get()->getWorld();
	ExploringScene* exploringScene = Game::get()->getExploringScene();

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

	int indexGroup = -1;
	


	while (!xmlVariables.empty())
	{
		XMLvariab var = xmlVariables.front();
		xmlVariables.erase(xmlVariables.begin());



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
		else if (var.name == "group")
		{
			indexGroup++;

			level.graphicTileLayer.deepOfLayer.push_back(0);

			std::vector<XMLvariab> copy = getXMLvariables(var.rawData);

			while (!copy.empty())
			{
				xmlVariables.emplace(xmlVariables.begin(), copy.back());

				copy.pop_back();
			}
		}
		else if (var.name == "layer")
		{
			//Update the counter of layer for this group
			level.graphicTileLayer.deepOfLayer[indexGroup]++;
			//Update the counter of layer for this group

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



			//Set all the Unique tiles to nullptr
			level.tileMap.uniqueTiles.resize(levelDim.x * levelDim.y * (zT + 1));


			for (posT.y = 0; posT.y < levelDim.y; posT.y++)
			{
				for (posT.x = 0; posT.x < levelDim.x; posT.x++)
				{
					level.tileMap.uniqueTiles[zT * levelDim.y * levelDim.x + posT.y * levelDim.x + posT.x] = nullptr;
				}
			}
			//Set all the Unique tiles to nullptr



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
					int logicType = 0;
					//Get the pos of the Tile
					Vector2i pos = { std::stoi(iter.getValue("x")), std::stoi(iter.getValue("y")) - world->currentLevel.tileSet->tileDim.y };
					pos = pos / world->currentLevel.tileSet->tileDim;
					//Get the pos of the Tile

					//Case is a standard Tile
					if (iter.getValue("gid") != "nothing")
					{
						logicType = std::stoi(iter.getValue("gid")) - firstGId;
					}
					//Case is a standard Tile
					
					//Case is a Unique Tile
					else
					{
						//Create the Unique Tile
						XMLvariab temp = *exploringScene->templatesUniqueTile[iter.getValue("template")];
						logicType = std::stoi(temp.getValue("gid")) - 1;

						//In case some properties are modified
						if (iter.withRawData)
						{
							//Delete the first line and last line("properties")
							iter.rawData.erase(iter.rawData.begin());
							iter.rawData.pop_back();
							//Delete the first line and last line("properties")

							//Iterate about properties that is changed
							std::vector<XMLvariab> propertiesChanged = getXMLvariables(iter.rawData);
							for (XMLvariab& prop : propertiesChanged)
								temp.values[prop.getValue("name")] = prop.getValue("value");
							//Iterate about properties that is changed
						}
						//In case some properties are modified

						//Add Unique Tile to the collection of the level of UniqueTile
						level.tileMap.uniqueTiles[zT * levelDim.y * levelDim.x + pos.y * levelDim.x + pos.x] = TileSystem::createUniqueTile(&temp);
						//Add Unique Tile to the collection of the level of UniqueTile

						//Create the Unique Tile
					}
					//Case is a Unique Tile

					//Set the logicType of Tile
					level.tileMap.tiles[zT * levelDim.y * levelDim.x + pos.y * levelDim.x + pos.x].logicType = static_cast<int>(logicType);
					//Set the logicType of Tile
				}
			}
			//Add particular object to this layer



			//Add a group of Entity
			level.groupsEntities.push_back(GroupEntity<>());
			//Add a group of Entity



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
#include "TileSet.h"

#include "Enviroment/TextureHandler.h"
#include "Enviroment/TextureHandler.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class TileSet
//-----------------------------------------------------------------------------------------------------------------------------------------
//PROBABLY ADD A TILEDIMENSION FROM VARIABLE TO PASS
TileSet* TileSetHandler::loadTileSet(const std::string& path, unsigned int tileDim)
{
	TileSet* tileSet = nullptr;
	tileSet = new TileSet;
	
	///PER ORA
	tileSet->tileDim = { static_cast<int>(tileDim), static_cast<int>(tileDim) };

	tileSet->texture = TextureHandler::get().getTexture(path);
	Vector2i textureDim = TextureHandler::get().getTextureDimension(path);
	tileSet->grid = { textureDim.x / tileSet->tileDim.x, 
				      textureDim.y / tileSet->tileDim.y };
	
	SDL_Rect src;
	src.w = tileSet->tileDim.x;
	src.h = tileSet->tileDim.y;

	tileSet->srcRects.resize(tileSet->grid.x * tileSet->grid.y);
	for (int y = 0; y < tileSet->grid.y; y++)
	{
		src.y = src.h * y;
		for (int x = 0; x < tileSet->grid.x; x++)
		{
			src.x = src.w * x;
			tileSet->srcRects[y * tileSet->grid.x + x] = src;
		}
	}

	mTileSets[path] = tileSet;

	return tileSet;
}



TileSet* TileSetHandler::getTileSet(const std::string& path)
{
	auto iter = mTileSets.find(path);

	if (iter != mTileSets.end())
	{
		return iter->second;
	}
	else
	{
		///ADD ASSERT
		return nullptr;
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class TileSet
//-----------------------------------------------------------------------------------------------------------------------------------------
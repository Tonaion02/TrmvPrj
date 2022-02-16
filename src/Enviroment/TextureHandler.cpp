#include "TextureHandler.h"

#include "SDL_Enviroment.h"

#include "Enviroment/WindowHandler.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class TextureHandler
//-----------------------------------------------------------------------------------------------------------------------------------------
TextureHandler::TextureHandler()
{
	if (!IMG_Init(IMG_INIT_PNG))
	{
		SDL_Log("\t-Error during initialization of SDL_Image: %s", SDL_GetError());
		exit(1);
	}
	SDL_Log("\t-SDL_Image initialization: success");
}



SDL_Texture* TextureHandler::getTexture(const std::string& path)
{
	auto iter = mTextures.find(path);
	if (iter != mTextures.end())
	{
		return iter->second;
	}
	else
	{
		return loadTexture(path);
	}
}



SDL_Texture* TextureHandler::loadTexture(const std::string& path)
{
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (!surface)
	{
		SDL_Log("Error in loading of image", SDL_GetError());
		return nullptr;
	}

	SDL_Texture* texture = nullptr;
	texture = SDL_CreateTextureFromSurface(WindowHandler::get().getRenderer(), surface);
	if (!texture)
	{
		SDL_Log("Error in conversion from surface to texture", SDL_GetError());
		return nullptr;
	}

	SDL_FreeSurface(surface);

	mTextures.emplace(path, texture);

	return texture;
}



Vector2i TextureHandler::getTextureDimension(const std::string& path)
{
	int w, h;
	SDL_QueryTexture(getTexture(path), nullptr, nullptr, &w, &h);
	return { w, h };
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class TextureHandler
//-----------------------------------------------------------------------------------------------------------------------------------------
#pragma once

#include <unordered_map>

#include "utils/Math/Math.h"





class TextureHandler
{
public:
	static TextureHandler& get()
	{
		static TextureHandler instance;
		return instance;
	}

	struct SDL_Texture* getTexture(const std::string& path);
	struct SDL_Texture* loadTexture(const std::string& path);
	Vector2i getTextureDimension(const std::string& path);

protected:
	TextureHandler();

protected:
	std::unordered_map<std::string, struct SDL_Texture*> mTextures;
};
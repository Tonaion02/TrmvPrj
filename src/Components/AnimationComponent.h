#pragma once

#include <unordered_map>





struct TiledAnimation
{
	std::vector<int> ids;
	float currentAnimation;
	float incrementIndex;
};





struct AnimationComponent
{
	std::unordered_map<int, TiledAnimation> animations;
};
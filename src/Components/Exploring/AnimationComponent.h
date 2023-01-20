#pragma once

#include <unordered_map>

#include "Data/TiledAnimation.h"





//First layer for actions
//Second layer for directions
struct AnimationComponent
{
	std::unordered_map<int, std::unordered_map<int, TiledAnimation>> animations;
	//std::unordered_map<int, TiledAnimation> animations;
	float currentId;
};
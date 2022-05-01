#pragma once

#include "utils/Math/Math.h"





using Camera = Entity;

struct CameraData
{
	Vector2f pos;
	Vector2i nTileToRender;
	Vector2i adj;
	float baseScale;
	Vector2i startToRender;
	Vector2i endToRender;
	float zoom;
	float minZoom;
	float maxZoom;
};
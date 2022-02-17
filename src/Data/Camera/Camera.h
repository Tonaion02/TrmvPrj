#pragma once

#include "Math/Math.h"





using Camera = Entity;

struct CameraData
{
	Vector2i nTileToRender;
	Vector2i adj;
	float baseScale;
	Vector2i startToRender;
	Vector2i endToRender;
	float zoom;

	///BOH
	float minZoom;
	float maxZoom;
};
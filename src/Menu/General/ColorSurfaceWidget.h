#pragma once

#include "utils/Math/Math.h"
#include "SDL_pixels.h"
#include "Menu/General/SizedWidget.h"





class ColorSurfaceWidget : public SizedWidget
{
public:
	ColorSurfaceWidget(const Vector2i& pos, const Vector2i& dim, const SDL_Color& color);

	virtual void init() override {}
	virtual void update() override {}
	virtual void draw() override;

protected:
	SDL_Color color;
};
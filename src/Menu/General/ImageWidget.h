#pragma once

#include "utils/Math/Vector2i.h"
#include "Menu/General/DrawableWidget.h"





class ImageWidget : public DrawableWidget
{
public:
	ImageWidget(struct SDL_Texture *image, const Vector2i& pos, const Vector2i& dim);

	virtual void init() override {}
	virtual void update() override {}
	virtual void draw() override;

protected:
	struct SDL_Texture *image;
};
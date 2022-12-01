#pragma once

#include "utils/Math/Math.h"
#include "Menu/General/SizedWidget.h"





class ImageWidget : public SizedWidget
{
public:
	ImageWidget(struct SDL_Texture *image, const Vector2i& pos, const Vector2i& dim);

	virtual void init() override {}
	virtual void update() override {}
	virtual void draw() override;

protected:
	struct SDL_Texture *image;
};
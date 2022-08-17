#pragma once

#include "utils/Math/Vector2i.h"

#include "Menu/General/Widget.h"





class DrawableWidget : public Widget
{
public:
	DrawableWidget(const Vector2i& pos, const Vector2i& dim);

	virtual void init() override {}
	virtual void update() override {}
	virtual void draw() override {};

	virtual void setPos(const Vector2i& pos);
	void setDim(const Vector2i& dim);
	Vector2i getPos() const;
	Vector2i getDim() const;
	struct SDL_Rect* getRect();

protected:
	struct SDL_Rect* rect;
};
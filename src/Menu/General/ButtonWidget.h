#pragma once

#include <functional>

#include "Menu/General/DrawableWidget.h"





class ButtonWidget : public DrawableWidget
{
public:
	ButtonWidget(const Vector2i& pos, const Vector2i& dim, class DrawableWidget* drawableWidget);

	void init() override { }
	void update() override;
	void draw() override;

	void setFunction(std::function<void()> f);
	void setPos(const Vector2i& pos) override;

protected:
	class DrawableWidget* drawableWidget;

	std::function<void()> function;
};
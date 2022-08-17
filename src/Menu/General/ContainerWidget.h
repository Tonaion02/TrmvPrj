#pragma once


#include "utils/Math/Vector2i.h"
#include "Menu/General/DrawableWidget.h"





class ContainerWidget : public DrawableWidget
{
public:
	ContainerWidget(class DrawableWidget* background, class DrawableWidget* child, const Vector2i& transformPosChild);

	virtual void init() override;
	virtual void update() override;
	virtual void draw() override;

	void setPos(const Vector2i& pos) override;

protected:
	class DrawableWidget* child;
	class DrawableWidget* background;
	Vector2i transformPosChild;
};
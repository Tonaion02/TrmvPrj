#pragma once


#include "utils/Math/Math.h"
#include "Menu/General/SizedWidget.h"





class ContainerWidget : public SizedWidget
{
public:
	ContainerWidget(class SizedWidget* background, class SizedWidget* child, const Vector2i& transformPosChild);

	virtual void init() override;
	virtual void update() override;
	virtual void draw() override;

	void setPos(const Vector2i& pos) override;

protected:
	class SizedWidget* child;
	class SizedWidget* background;
	Vector2i transformPosChild;
};
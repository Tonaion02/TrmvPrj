#pragma once

#include <array>

#include "Menu/General/DrawableWidget.h"





template<unsigned int NumChildrens>
class VerticalGroupWidget : public DrawableWidget
{
public:
	VerticalGroupWidget(const Vector2i& pos, const std::array<class DrawableWidget*, NumChildrens>& childrens)
		:DrawableWidget(pos, { 0, 0 }), childrens(childrens)
	{

	}

	void init() override
	{
		Vector2i pos = this->getPos();
		int x = 0;

		for (auto it : childrens)
		{
			it->setPos(pos);

			pos.y += it->getDim().y;
			if (x < it->getDim().x)
				x = getDim().x;
		}

		pos.x = x;
		this->setDim(pos);



		for (auto it : childrens)
		{
			it->init();
		}
	}
	void update() override
	{
		for (auto it : childrens)
			it->update();
	}
	void draw() override
	{
		for (auto it : childrens)
			it->draw();
	}

	void setPos(const Vector2i& pos)
	{
		this->rect->x = pos.x;
		this->rect->y = pos.y;

		Vector2i p = pos;
		int x = 0;

		for (auto it : childrens)
		{
			it->setPos(p);

			p.y += it->getDim().y;
			if (x < it->getDim().x)
				x = getDim().x;
		}
	}

	unsigned int getNumButtons()
	{
		return childrens.size();
	}

protected:
	std::array<class DrawableWidget*, NumChildrens> childrens;
};
#include "Menu/General/ColorSurfaceWidget.h"

#include "Enviroment/WindowHandler.h"

#include "SDL_Enviroment.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class ColorSurfaceWidget
//-----------------------------------------------------------------------------------------------------------------------------------------
ColorSurfaceWidget::ColorSurfaceWidget(const Vector2i& pos, const Vector2i& dim, const SDL_Color& color)
	:SizedWidget(pos, dim), color(color)
{

}



void ColorSurfaceWidget::draw()
{
	SDL_SetRenderDrawColor(WindowHandler::get().getRenderer(), color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(WindowHandler::get().getRenderer(), this->rect);
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class ColorSurfaceWidget
//-----------------------------------------------------------------------------------------------------------------------------------------
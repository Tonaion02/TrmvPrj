#include "Menu/General/ImageWidget.h"

#include "Enviroment/WindowHandler.h"

#include "SDL_Enviroment.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class ImageWidget
//-----------------------------------------------------------------------------------------------------------------------------------------
ImageWidget::ImageWidget(struct SDL_Texture *image, const Vector2i& pos, const Vector2i& dim)
	:SizedWidget(pos, dim), image(image)
{

}



void ImageWidget::draw()
{
	SDL_RenderCopy(WindowHandler::get().getRenderer(), image, nullptr, this->getRect());
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class ImageWidget
//-----------------------------------------------------------------------------------------------------------------------------------------
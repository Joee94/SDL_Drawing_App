#include "Rectangle.h"

Rectangle::Rectangle()
{
	point1 = new Vec2();
	point2 = new Vec2();
}

Rectangle::~Rectangle()
{
	delete point1;
	delete point2;
}

void Rectangle::Draw(SDL_Renderer* renderer)
{
	SDL_Rect temp = {point1->x, point1->y, point2->x- point1->x, point2->y - point1->y}; 
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderDrawRect(renderer, &temp); 
}

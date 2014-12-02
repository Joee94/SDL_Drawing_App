#include "Rectangle.h"

Rectangle::Rectangle()
{
   //Create some points...
	point1 = new Vec2();
	point2 = new Vec2();
}

Rectangle::~Rectangle()
{
   //...Destroy some points
	delete point1;
	delete point2;
}

void Rectangle::Draw(SDL_Renderer* renderer)
{
   //Another easy one, create a rectangle then draw it, don't erally see WHY I have to create one before drawing it but I'm sure it has its benefits
	SDL_Rect temp = {point1->x, point1->y, point2->x- point1->x, point2->y - point1->y}; 
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderDrawRect(renderer, &temp); 
}


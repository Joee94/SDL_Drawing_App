#include "Rectangle.h"

Rectangle::Rectangle()
{
	corner1 = new Vec2();
	corner2 = new Vec2();
}

Rectangle::~Rectangle()
{
	delete corner1;
	delete corner2;
}

void Rectangle::Corner(SDL_Event& mouseEvent, SDL_Renderer* renderer)
{
	switch(mouseEvent.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		corner1->x = mouseEvent.button.x;
		corner1->y = mouseEvent.button.y;
		break;
		
	case SDL_MOUSEBUTTONUP:
		corner2->x = mouseEvent.button.x;
		corner2->y = mouseEvent.button.y;
		break;

	}
}

void Rectangle::Draw(SDL_Renderer* renderer)
{
	SDL_Rect temp = {corner1->x, corner1->y, corner2->x- corner1->x, corner2->y - corner1->y}; 
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderDrawRect(renderer, &temp); 
}

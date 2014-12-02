#include "StraightLine.h"

StraightLine::StraightLine()
{
   //Create some points...
	point1 = new Vec2();
	point2 = new Vec2();
}

StraightLine::~StraightLine()
{
   //...Destroy some points
	delete point1;
	delete point2;
}

void StraightLine::Draw(SDL_Renderer* renderer)
{
   //This is an easy one, set a colour and draw it, thanks to inheritance I don't have to worry about the mouseinput stuff
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderDrawLine(renderer, point1->x, point1->y, point2->x, point2->y); 
}

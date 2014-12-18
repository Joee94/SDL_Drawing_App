#include "StraightLine.h"

StraightLine::StraightLine()
{
   //Create some points...
	point1 = new Vec2();
   point2 = new Vec2();
   shapeType = 0;
}

StraightLine::~StraightLine()
{
   //...Destroy some points
	delete point1;
	delete point2;
}

void StraightLine::Draw(SDL_Renderer* renderer, float r, float g, float b, float a)
{
   //This is an easy one, set a colour and draw it, thanks to inheritance I don't have to worry about the mouseinput stuff
	SDL_SetRenderDrawColor( renderer, r, g, b, a );
	SDL_RenderDrawLine(renderer, point1->x, point1->y, point2->x, point2->y); 
}

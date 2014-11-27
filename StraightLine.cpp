#include "StraightLine.h"

StraightLine::StraightLine()
{
	point1 = new Vec2();
	point2 = new Vec2();
}

StraightLine::~StraightLine()
{
	delete point1;
	delete point2;
}

void StraightLine::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderDrawLine(renderer, point1->x, point1->y, point2->x, point2->y); 
}

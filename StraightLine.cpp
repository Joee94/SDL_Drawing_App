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

void StraightLine::Point(SDL_Event& mouseEvent, SDL_Renderer* renderer)
{
	switch(mouseEvent.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		point1->x = mouseEvent.button.x;
		point1->y = mouseEvent.button.y;
		break;
		
	case SDL_MOUSEBUTTONUP:
		point2->x = mouseEvent.button.x;
		point2->y = mouseEvent.button.y;
		break;

	}
}

void StraightLine::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderDrawLine(renderer, point1->x, point1->y, point2->x, point2->y); 
}

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
   SDL_SetRenderDrawColor(renderer, r, g, b, a);
   //Some thickness stuff... maybe soon
   //float angle = atan2f(point2->y - point1->y, point2->x - point1->x);
   //float x0, x1, y0, y1 = 0;
   //
   //for (int i = 0; i < 10; ++i)
   //{
   //   x0 = point1->x + i * cos(angle + PI/2);
   //   y0 = point1->y + i * sin(angle + PI/2);
   //   x1 = point2->x + i * cos(angle + PI/2);
   //   y1 = point2->y + i * sin(angle + PI/2);
   //   SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
   //}
   SDL_RenderDrawLine(renderer, point1->x, point1->y, point2->x,point2->y);
}

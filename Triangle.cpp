#include "Triangle.h"

Triangle::Triangle()
{
   //Create some points...
   point1 = new Vec2();
   point2 = new Vec2();
   controlPoint = new Vec2(); //eh, it's actually just a 3rd point but this means I don't have to make a new variable
   controlPoint2 = new Vec2(); //This is here because I'm lazy
   shapeType = 5;
}

Triangle::~Triangle()
{
   //...Destroy some points
   delete point1;
   delete point2;
   delete controlPoint;
   delete controlPoint2;
}

void Triangle::Draw(SDL_Renderer* renderer, float r, float g, float b, float a)
{
   SDL_SetRenderDrawColor(renderer, r, g, b, a);
   SDL_RenderDrawLine(renderer, point1->x, point1->y, point2->x, point2->y);
   SDL_RenderDrawLine(renderer, point2->x, point2->y, controlPoint->x, controlPoint->y);
   SDL_RenderDrawLine(renderer, controlPoint->x, controlPoint->y, point1->x, point1->y);
}

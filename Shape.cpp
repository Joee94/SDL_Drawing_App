#include "Shape.h"

void Shape::Point(SDL_Event& mouseEvent, SDL_Renderer* renderer)
{
   switch (mouseEvent.type)
   {
   case SDL_MOUSEBUTTONDOWN:
      point1->x = mouseEvent.button.x;
      point1->y = mouseEvent.button.y;

      point2->x = mouseEvent.button.x;
      point2->y = mouseEvent.button.y;
      break;


   case SDL_MOUSEBUTTONUP:
      point2->x = mouseEvent.button.x;
      point2->y = mouseEvent.button.y;
      break;

   }
}

void Shape::Point(SDL_Renderer* renderer, float p1x, float p1y, float p2x, float p2y)
{
   point1->x = p1x;
   point1->y = p1y;
   point2->x = p2x;
   point2->y = p2y;
}

void Shape::Draw(SDL_Renderer* renderer)
{
}

Vec2 Shape::GetPoint1()
{
   return (*this->point1);
}

Vec2 Shape::GetPoint2()
{
   return (*this->point2);
}
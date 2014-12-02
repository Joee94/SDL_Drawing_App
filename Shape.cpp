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

void Shape::Point(SDL_Renderer* renderer, Vec2 p1, Vec2 p2)
{
   point1->x = p1.x;
   point1->y = p1.y;
   point2->x = p2.x;
   point2->y = p2.y;
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
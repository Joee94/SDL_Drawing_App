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

void Shape::Point(SDL_Event& mouseEvent, SDL_Renderer* renderer, int num)
{
   //had to use a "num" thing here because I'm using mouseup twice
   switch (num)
   {
   case 0:
      //I plot all three points when mouse is pressed otherwise I get a bug where the point is initialised to 0,0 immediately and things just go wrong until you plot the other points
      point1->x = mouseEvent.button.x;
      point1->y = mouseEvent.button.y;
      point2->x = mouseEvent.button.x;
      point2->y = mouseEvent.button.y;
      controlPoint->x = mouseEvent.button.x;
      controlPoint->y = mouseEvent.button.y;
      break;
   case 1:
      point2->x = mouseEvent.button.x;
      point2->y = mouseEvent.button.y;
      break;
   case 2:
      controlPoint->x = mouseEvent.button.x;
      controlPoint->y = mouseEvent.button.y;
      break;
   }
}

void Shape::Point(SDL_Renderer* renderer, float p1x, float p1y, float p2x, float p2y, float p3x, float p3y)
{
   point1->x = p1x;
   point1->y = p1y;
   point2->x = p2x;
   point2->y = p2y;
   controlPoint->x = p3x;
   controlPoint->y = p3y;
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

Vec2 Shape::GetControlPoint()
{
   return (*this->controlPoint);
}

int Shape::GetShapeType()
{
   return (this->shapeType);

}
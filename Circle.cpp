#include "Circle.h"

Circle::Circle()
{
	point1 = new Vec2();
	point2 = new Vec2();
}

Circle::~Circle()
{
	delete point1;
	delete point2;
}

void Circle::Draw(SDL_Renderer* renderer)
{
   int x0 = point1->x;
   int y0 = point1->y;
   int radiusx = fabs(point2->x - point1->x);
   int radiusy = fabs(point2->y - point1->y);
   radius = sqrt((radiusx*radiusx) + (radiusy*radiusy));
   int x = radius;
   int y = 0;
   radiusError = 1 - x;

   std::cout << point1->x << std::endl;
   std::cout << point1->y << std::endl;
   std::cout << point2->x << std::endl;
   std::cout << point2->y << std::endl;
   std::cout << radius << std::endl;
   std::cout << std::endl;

   #pragma omp parallel for
   for (y = 0; x >= y; y++)
   {
      SDL_RenderDrawPoint(renderer, x + x0, y + y0);		//Completely and utterly stolen from http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
      SDL_RenderDrawPoint(renderer, y + x0, x + y0);
      SDL_RenderDrawPoint(renderer, -x + x0, y + y0);
      SDL_RenderDrawPoint(renderer, -y + x0, x + y0);
      SDL_RenderDrawPoint(renderer, -x + x0, -y + y0);
      SDL_RenderDrawPoint(renderer, -y + x0, -x + y0);
      SDL_RenderDrawPoint(renderer, x + x0, -y + y0);
      SDL_RenderDrawPoint(renderer, y + x0, -x + y0);

      if (radiusError < 0)
      {
         radiusError += 2 * y + 1;
      }
      else
      {
         x--;
         radiusError += 2 * (y - x + 1);
      }
   }

	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
}

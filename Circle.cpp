#include "Circle.h"

Circle::Circle()
{
   //Creating the points
	point1 = new Vec2();
   point2 = new Vec2();
   shapeType = 2;
}

Circle::~Circle()
{
   //Deleting the points
	delete point1;
	delete point2;
}

void Circle::Draw(SDL_Renderer* renderer, float r, float g, float b, float a)
{
   //Ok I'm not 100% sure how this works, circles are complicated
   
   float x0 = point1->x;  //assign my point1 co-ordinates to x0 and y0
   float y0 = point1->y;
   float radiusx = fabs(point2->x - point1->x);   //find the radius, for some reason length doesn't work or something... idk
   float radiusy = fabs(point2->y - point1->y);   //I HATE this piece of code it's so terribly innefficient
   radius = sqrt((radiusx*radiusx) + (radiusy*radiusy));
   //radius = length(point1 - point2);    //Why doesn't this work.... WHYYY
   float x = radius;   //set x as the radius
   float y = 0;  //set y as the center point (I think)
   radiusError = 1 - x;

   #ifdef _DEBUG
   std::cout << point1->x << std::endl;   //Debugging stuff
   std::cout << point1->y << std::endl;
   std::cout << point2->x << std::endl;
   std::cout << point2->y << std::endl;
   std::cout << radius << std::endl;
   std::cout << std::endl;
   #endif

   SDL_SetRenderDrawColor(renderer, r, g, b, a);


	   for (float angle = -PI; angle <= PI; angle += 0.1)
	   {
		   Vec2 p(cos(angle), sin(angle));
		   SDL_RenderDrawPoint(renderer, p.x / 2, p.y/2);
	   }


  //#pragma omp parallel for
  //for (y = 0; x >= y; y++)
  //{
  //   //Yeah I'm not gunna lie I'm not sure what's going on here... just drawing a buncha points
  //   SDL_RenderDrawPoint(renderer, x + x0, y + y0);		//Completely and utterly stolen from http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
  //   SDL_RenderDrawPoint(renderer, y + x0, x + y0);
  //   SDL_RenderDrawPoint(renderer, -x + x0, y + y0);
  //   SDL_RenderDrawPoint(renderer, -y + x0, x + y0);
  //   SDL_RenderDrawPoint(renderer, -x + x0, -y + y0);
  //   SDL_RenderDrawPoint(renderer, -y + x0, -x + y0);
  //   SDL_RenderDrawPoint(renderer, x + x0, -y + y0); 
  //   SDL_RenderDrawPoint(renderer, y + x0, -x + y0);
  //
  //   if (radiusError < 0)
  //   {
  //      radiusError += 2 * y + 1;
  //   }
  //   else
  //   {
  //      x--;
  //      radiusError += 2 * (y - x + 1);
  //   }
  //}

}

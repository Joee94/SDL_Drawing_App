#include "CurvedLine.h"

CurvedLine::CurvedLine()
{
   //Create some points...
   point1 = new Vec2();
   point2 = new Vec2();
   controlPoint = new Vec2();
}

CurvedLine::~CurvedLine()
{
   //...Destroy some points
   delete point1;
   delete point2;
   delete controlPoint;
}


//Need to take the point class and draw a third point for the control point........

void CurvedLine::Draw(SDL_Renderer* renderer)
{
	float startX = point1->x;
	float startY = point1->y;

   #ifdef _DEBUG  
   //Lines to see where the control points are
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	SDL_RenderDrawLine(renderer, (int)point1->x, (int)point1->y, (int)controlPoint->x, (int)controlPoint->y);
	SDL_RenderDrawLine(renderer, (int)controlPoint->x, (int)controlPoint->y, (int)point2->x, (int)point2->y);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawPoint(renderer, controlPoint->x, controlPoint->y);
   #endif


	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
   //Parallel for loop learnt from rob
   #pragma omp parallel for
   for (int i = 1; i < numSamples; ++i)
   {
      //Once again, not sure how this works but it draws a pretty line
     float t = (float)i / (float)numSamples;
     //Calling the function to calculate everything
	  Vec2 end = QuadBezierSample2(*point1, *point2, *controlPoint, t);

     //Then draw the line where it needs to go
	  SDL_RenderDrawLine(renderer, startX, startY, end.x, end.y);

     //Then the new starting point of the next line will be the end of the last line
	  startX = end.x;
	  startY = end.y;
   }

   //When it's all done connect it up
   SDL_RenderDrawLine(renderer, startX, startY, point2->x, point2->y);
}

void CurvedLine::Point(SDL_Event& mouseEvent, SDL_Renderer* renderer, int num)
{
   //had to use a "num" thing here because I'm using mouseup twice
	switch (num)
	{
	case 0:
      //I plot all three points when mosuedown is pressed otherwise I get a bug where the point is initialised to 0,0 immediately and things just go wrong until you plot the other points
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

Vec2 CurvedLine::QuadBezierSample2(Vec2 a, Vec2 b, Vec2 control, float t)
{
   //Magic...
	return ((1.0f - t)*(1.0f - t)*a) + (2.0f*(1.0f - t)*t*control) + (t*t*b);
}

void CurvedLine::Point(SDL_Renderer* renderer, float p1x, float p1y, float p2x, float p2y, float p3x, float p3y)
{
   point1->x = p1x;
   point1->y = p1y;
   point2->x = p2x;
   point2->y = p2y;
   controlPoint->x = p3x;
   controlPoint->y = p3y;
}

Vec2 CurvedLine::GetControlPoint()
{
   return (*this->controlPoint);
}
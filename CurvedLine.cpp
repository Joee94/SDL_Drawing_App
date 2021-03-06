#include "CurvedLine.h"

CurvedLine::CurvedLine()
{
   //Create some points...
   point1 = new Vec2();
   point2 = new Vec2();
   controlPoint = new Vec2();
   controlPoint2 = new Vec2(); //This is here because I'm lazy
   shapeType = 3;
}

CurvedLine::~CurvedLine()
{
   //...Destroy some points
   delete point1;
   delete point2;
   delete controlPoint;
   delete controlPoint2;
}


//Need to take the point class and draw a third point for the control point........

void CurvedLine::Draw(SDL_Renderer* renderer, float r, float g, float b, float a)
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

   SDL_SetRenderDrawColor(renderer, r, g, b, a);
   for (int i = 1; i < numSamples; ++i)
   {
      //Once again, not sure how this works but it draws a pretty line
      float t = (float)i / (float)numSamples;
      //Calling the function to calculate everything
      Vec2 end = QuadBezierSample(*point1, *point2, *controlPoint, t);

      //Then draw the line where it needs to go
      SDL_RenderDrawLine(renderer, startX, startY, end.x, end.y);

      //Then the new starting point of the next line will be the end of the last line
      startX = end.x;
      startY = end.y;
   }

   //When it's all done connect it up
   SDL_RenderDrawLine(renderer, startX, startY, point2->x, point2->y);
}

//Stolen from Leigh's code
Vec2 CurvedLine::QuadBezierSample(Vec2 a, Vec2 b, Vec2 control, float t)
{
   return ((1.0f - t)*(1.0f - t)*a) + (2.0f*(1.0f - t)*t*control) + (t*t*b);
}
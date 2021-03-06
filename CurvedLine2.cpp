#include "CurvedLine2.h"

CurvedLine2::CurvedLine2()
{
   //Create some points...
   point1 = new Vec2();
   point2 = new Vec2();
   controlPoint = new Vec2();
   controlPoint2 = new Vec2();
   shapeType = 4;
}

CurvedLine2::~CurvedLine2()
{
   //...Destroy some points
   delete point1;
   delete point2;
   delete controlPoint;
   delete controlPoint2;
}


//Need to take the point class and draw a third point for the control point........

void CurvedLine2::Draw(SDL_Renderer* renderer, float r, float g, float b, float a)
{
   float startX = point1->x;
   float startY = point1->y;

#ifdef _DEBUG  
   //Lines to see where the control points are
   SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
   SDL_RenderDrawLine(renderer, (int)point1->x, (int)point1->y, (int)controlPoint->x, (int)controlPoint->y);
   SDL_RenderDrawLine(renderer, (int)controlPoint->x, (int)controlPoint->y, (int)controlPoint2->x, (int)controlPoint2->y);
   SDL_RenderDrawLine(renderer, (int)controlPoint2->x, (int)controlPoint2->y, (int)point2->x, (int)point2->y);
   SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
   SDL_RenderDrawPoint(renderer, controlPoint->x, controlPoint->y);
#endif


   SDL_SetRenderDrawColor(renderer, r, g, b, a);
   for (int i = 1; i < numSamples; ++i)
   {
      //Once again, not sure how this works but it draws a pretty line
      float t = (float)i / (float)numSamples;
      //Calling the function to calculate everything
      Vec2 end = CubicBezierSample(*point1, *point2, *controlPoint, *controlPoint2, t);

      //Then draw the line where it needs to go
      SDL_RenderDrawLine(renderer, startX, startY, end.x, end.y);

      //Then the new starting point of the next line will be the end of the last line
      startX = end.x;
      startY = end.y;
   }

   //When it's all done connect it up
   SDL_RenderDrawLine(renderer, startX, startY, point2->x, point2->y);
}

//Stolen from Leigh's code + the algorithm from http://en.wikipedia.org/wiki/B%C3%A9zier_curve#Constructing_B.C3.A9zier_curves
Vec2 CurvedLine2::CubicBezierSample(Vec2 a, Vec2 b, Vec2 control, Vec2 control2, float t)
{
   //     (1-t^3)P0                              + 3(1-t)^2P1                             + 3(1-t)t^2P2                    + t^3P3
   return (((1.0f - t)*(1.0f - t)*(1.0f - t))*a) + (3.0f*(1.0f - t)*(1.0f - t)*t*control) + (3.0f*(1.0f - t)*t*t*control2) + (t*t*t*b);
}

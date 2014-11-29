#include "CurvedLine.h"

CurvedLine::CurvedLine()
{
   point1 = new Vec2();
   point2 = new Vec2();

}

CurvedLine::~CurvedLine()
{
   delete point1;
   delete point2;
}


//Need to take the point class and draw a third point for the control point........

void CurvedLine::Draw(SDL_Renderer* renderer)
{
   SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
   SDL_RenderDrawLine(renderer, point1->x, point1->y, point2->x, point2->y);

   for (int i = 0; i < numSamples; ++i)
   {
      float t = (float)i / (float)numSamples;
      Vec2 end = QuadBezierSample(*point1, *point2, *point3, controlPoint, t)
   }
}

Vec2 QuadBezierSample(Vec2 point1, Vec2 point2, Vec2 control, float t)
{
   return ((1.0f - t)*(1.0f - t)*point.x) + (2.0f*(1.0f - t)*t*control) + (t*t*point.y);
}
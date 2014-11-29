#include "CurvedLine.h"

CurvedLine::CurvedLine()
{
   point1 = new Vec2();
   point2 = new Vec2();
   controlPoint = new Vec2();

}

CurvedLine::~CurvedLine()
{
   delete point1;
   delete point2;
   delete controlPoint;
}


//Need to take the point class and draw a third point for the control point........

void CurvedLine::Draw(SDL_Renderer* renderer)
{
	float startX = point1->x;
	float startY = point1->y;

	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	SDL_RenderDrawLine(renderer, (int)point1->x, (int)point1->y, (int)controlPoint->x, (int)controlPoint->y);
	SDL_RenderDrawLine(renderer, (int)controlPoint->x, (int)controlPoint->y, (int)point2->x, (int)point2->y);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawPoint(renderer, controlPoint->x, controlPoint->y);


	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
   for (int i = 1; i < numSamples; ++i)
   {
      float t = (float)i / (float)numSamples;
	  Vec2 end = QuadBezierSample2(*point1, *point2, *controlPoint, t);

	  SDL_RenderDrawLine(renderer, startX, startY, end.x, end.y);

	  startX = end.x;
	  startY = end.y;
   }

   SDL_RenderDrawLine(renderer, startX, startY, point2->x, point2->y);
}

void CurvedLine::Point2(SDL_Event& mouseEvent, SDL_Renderer* renderer, int num)
{
	switch (num)
	{
	case 0:
		point1->x = mouseEvent.button.x;
		point1->y = mouseEvent.button.y;
		break;
	case 1:
		point2->x = mouseEvent.button.x;
		point2->y = mouseEvent.button.y;
		break;
	case 2:
		controlPoint->x = mouseEvent.button.x;
		controlPoint->y = mouseEvent.button.x;
		break;
	}
}

Vec2 CurvedLine::QuadBezierSample2(Vec2 a, Vec2 b, Vec2 control, float t)
{
	return ((1.0f - t)*(1.0f - t)*a) + (2.0f*(1.0f - t)*t*control) + (t*t*b);
}
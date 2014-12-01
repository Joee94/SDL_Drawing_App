#pragma once
#include "Shape.h"

class CurvedLine : public Shape
{
public:
   CurvedLine();
   ~CurvedLine();

   std::vector<CurvedLine*> curvedlines;
   void Draw(SDL_Renderer* renderer);
   void Point(SDL_Event& mouseEvent, SDL_Renderer* renderer, int num);
   Vec2 CurvedLine::QuadBezierSample2(Vec2 a, Vec2 b, Vec2 control, float t);

private:
	Vec2* point1;
	Vec2* point2;
	Vec2* controlPoint;
	int numSamples = 100;
	
	float QuadBezierSample(float a, float b, float control, float t);
};
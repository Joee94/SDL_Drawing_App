#pragma once
#include "Shape.h"

//Inherit from shape
class CurvedLine : public Shape
{
public:
   //A bit more complicated
   CurvedLine();
   ~CurvedLine();

   //All my functions are different this time
   void Draw(SDL_Renderer* renderer);
   void Point(SDL_Event& mouseEvent, SDL_Renderer* renderer, int num);
   Vec2 CurvedLine::QuadBezierSample2(Vec2 a, Vec2 b, Vec2 control, float t);

private:
   //Some classic private variables
	Vec2* point1;
	Vec2* point2;
	Vec2* controlPoint;
	int numSamples = 100;
	
	float QuadBezierSample(float a, float b, float control, float t);
};
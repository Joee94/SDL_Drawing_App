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
   void Point(SDL_Renderer* renderer, float p1x, float p1y, float p2x, float p2y, float p3x, float p3y);
   Vec2 CurvedLine::QuadBezierSample2(Vec2 a, Vec2 b, Vec2 control, float t);


   Vec2 CurvedLine::GetControlPoint();

private:
   //Some classic private variables
	Vec2* controlPoint;
	int numSamples = 100;
	
	float QuadBezierSample(float a, float b, float control, float t);
};
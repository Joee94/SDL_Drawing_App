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
   void CurvedLine::Draw(SDL_Renderer* renderer);
   Vec2 CurvedLine::QuadBezierSample2(Vec2 a, Vec2 b, Vec2 control, float t);


   Vec2 CurvedLine::GetControlPoint();

private:
   //Some classic private variables
	int numSamples = 100;
	
	float QuadBezierSample(float a, float b, float control, float t);
};
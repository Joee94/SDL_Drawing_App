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
   void Draw(SDL_Renderer* renderer, float r, float g, float b, float a);
   Vec2 QuadBezierSample2(Vec2 a, Vec2 b, Vec2 control, float t);
   Vec2 GetControlPoint();

private:
   //Some classic private variables
	int numSamples = 100;
	
	float QuadBezierSample(float a, float b, float control, float t);
};
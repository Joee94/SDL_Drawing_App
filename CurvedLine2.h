#pragma once
#include "Shape.h"

//Inherit from shape
class CurvedLine2 : public Shape
{
public:
   //A bit more complicated
   CurvedLine2();
   ~CurvedLine2();

   //All my functions are different this time
   void Draw(SDL_Renderer* renderer, float r, float g, float b, float a);
   Vec2 CubicBezierSample(Vec2 a, Vec2 b, Vec2 control, Vec2 control2, float t);
   Vec2 GetControlPoint();
   Vec2 GetControlPoint2();

private:
   //Some classic private variables
   int numSamples = 100;
};
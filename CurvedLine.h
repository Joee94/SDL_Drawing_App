#pragma once
#include "Shape.h"

class CurvedLine : public Shape
{
public:
   CurvedLine();
   ~CurvedLine();

   std::vector<CurvedLine*> lines;
   void Draw(SDL_Renderer* renderer);

private:
   Vec2* controlPoint;
   float numSamples = 100.0f;

   Vec2 QuadBezierSample(Vec2 point, float control, float t);
};
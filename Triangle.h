#pragma once
#include "Shape.h"
class Triangle : public Shape
{
public:
   Triangle();
   ~Triangle();

   void Draw(SDL_Renderer* renderer, float r, float g, float b, float a);
};


#pragma once
#include "Shape.h"

//Inherit from Shape
class Circle : public Shape
{
public:
   //Just a constructor, Destructor and a funtion
   Circle();
   ~Circle();

   void Draw(SDL_Renderer* renderer, float r, float g, float b, float a);

private:
   //some private variables for working things out
   float radius;
   float radiusError;
};

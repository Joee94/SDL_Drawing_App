#pragma once
#include "Shape.h"

/// The Circle class
class Circle : public Shape
{
public:
   /// \brief Circle constructor
   Circle();
   /// \brief Circle destructor
   ~Circle();

   void Draw(SDL_Renderer* renderer, float r, float g, float b, float a);

private:
   //some private variables for working things out
   float radius;  ///<The circle radius
   float radiusError;   ///<The circle error
};

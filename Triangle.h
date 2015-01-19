#pragma once
#include "Shape.h"

/// The triangle class
class Triangle : public Shape
{
public:
   /// \brief Triangle constructor
   Triangle();
   /// \brief Triangle destructor
   ~Triangle();

   void Draw(SDL_Renderer* renderer, float r, float g, float b, float a);
};


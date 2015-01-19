#pragma once
#include "Shape.h"

/// The Rectangle class
class Rectangle : public Shape
{
public:
   /// \brief Rectangle constructor
   Rectangle();
   /// \brief Rectangle destructor
   ~Rectangle();

   void Draw(SDL_Renderer* renderer, float r, float g, float b, float a);
};
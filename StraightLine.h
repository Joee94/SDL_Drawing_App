#pragma once
#include "Shape.h"

/// The Straight Line class
class StraightLine : public Shape
{
public:
   /// \brief Striaght Line constructor
   StraightLine();
   /// \brief Striaght Line destructor
   ~StraightLine();

   void Draw(SDL_Renderer* renderer, float r, float g, float b, float a);
};
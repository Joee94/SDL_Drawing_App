#pragma once
#include "Vec2.h"
#include "SDL.h"

/// The class for position functions
class Position
{
public:
   Position();
   ~Position();

   /// \brief Returns the position your mouse is currently in as a Vec2
   /// \param mouseEvent your mouse data
   Vec2 GetPosition(SDL_Event& mouseEvent);

   /// \brief Checks whether your mouse is within a rectangle
   /// \param mouseEvent your mouse data
   /// \param topleft the top left point of the rectangle
   /// \param bottomright the bottom right point of the rectangle
   bool CheckPosition(SDL_Event& mouseEvent, Vec2 topleft, Vec2 bottomright);

private:
   Vec2* point;
};
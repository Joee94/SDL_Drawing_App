#pragma once
#include "Vec2.h"
#include "SDL.h"
class Position
{
public:
   Position();
   ~Position();

   Vec2 GetPosition(SDL_Event& mouseEvent);
   bool CheckPosition(SDL_Event& mouseEvent, Vec2 topleft, Vec2 bottomright);

private:
   Vec2* point;
};
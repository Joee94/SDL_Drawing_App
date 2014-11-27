#pragma once
#include <SDL.h>
#include <vector>
#include <iostream>
#include "Vec2.h"

class Shape
{
public:
   std::vector<Shape*> shapes;
   void Point(SDL_Event& mouseEvent, SDL_Renderer* renderer);
   void Draw(SDL_Renderer* renderer);

protected:

   Vec2* point1;
   Vec2* point2;
};
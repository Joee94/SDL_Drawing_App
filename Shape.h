#pragma once
#include <SDL.h>
#include <vector>
#include <iostream>
#include "Vec2.h"

//This is the base Shape class that all classes will inherit

class Shape
{
public:
   //std::vector<Shape*> shapes;
   virtual void Point(SDL_Event& mouseEvent, SDL_Renderer* renderer);   //Virtual so I can overwrite them when I need to
   virtual void Point(SDL_Renderer* renderer, float p1x, float p2x, float p1y, float p2y);
   virtual void Draw(SDL_Renderer* renderer);

   Vec2 GetPoint1();
   Vec2 GetPoint2();

protected:
   Vec2* point1;  //My base 2 points which all shapes have however some may have more points
   Vec2* point2;
};
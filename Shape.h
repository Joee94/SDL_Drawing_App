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
   virtual void Point(SDL_Event& mouseEvent);   //Virtual so I can overwrite them when I need to
   virtual void Point(float p1x, float p2x, float p1y, float p2y);
   virtual void Point(SDL_Event& mouseEvent, int num);
   virtual void Point(float p1x, float p1y, float p2x, float p2y, float p3x, float p3y);
   virtual void Point2(SDL_Event& mouseEvent);
   virtual void Draw(SDL_Renderer* renderer, float r, float g, float b, float a);
   virtual void Colour(uint8_t &red, uint8_t &green, uint8_t &blue, uint8_t &alpha);

   Vec2 GetPoint1();
   Vec2 GetPoint2();
   Vec2 GetControlPoint();
   uint8_t GetShapeType();
   uint8_t GetR();
   uint8_t GetG();
   uint8_t GetB();
   uint8_t GetA();

protected:
   Vec2* point1;  //My base 2 points which all shapes have however some may have more points
   Vec2* point2;
   Vec2* controlPoint;

   uint8_t r;
   uint8_t g;
   uint8_t b;
   uint8_t a;

   uint8_t shapeType;
};
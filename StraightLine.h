#pragma once
#include "Shape.h"
#include "glew.h"

//Inherit from Shape
class StraightLine : public Shape
{
public:
   //Just a constructor, Destructor and a funtion
	StraightLine();
	~StraightLine();

   void Draw(SDL_Renderer* renderer, float r, float g, float b, float a);
   void CreateArray(SDL_Event& mouseEvent);
   void glDraw();
};
#pragma once
#include "Shape.h"

//Inherit from Shape
class Rectangle : public Shape
{
public:
   //Constructor and Destructor... standard
	Rectangle();
	~Rectangle();

   //Just a draw function
   void Draw(SDL_Renderer* renderer, float r, float g, float b, float a);
};
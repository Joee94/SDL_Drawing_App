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
   void Rectangle::Draw(SDL_Renderer* renderer);
};
#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle();
	~Rectangle();

   std::vector<Rectangle*> rectangles;
   void Rectangle::Draw(SDL_Renderer* renderer);
};
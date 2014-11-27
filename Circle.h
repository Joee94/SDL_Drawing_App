#pragma once
#include "Shape.h"

class Circle : public Shape
{
public:
	Circle();
	~Circle();

   std::vector<Circle*> lines;
	void Draw(SDL_Renderer* renderer);

private:
	float radius;
	float radiusError;
};

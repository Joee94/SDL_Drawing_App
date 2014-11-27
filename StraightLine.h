#pragma once
#include "Shape.h"

class StraightLine : public Shape
{
public:
	StraightLine();
	~StraightLine();

   std::vector<StraightLine*> lines;
	void Draw(SDL_Renderer* renderer);
};
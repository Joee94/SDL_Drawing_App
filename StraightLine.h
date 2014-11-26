#pragma once
#include <SDL.h>
#include <vector>
#include <iostream>
#include "Vec2.h"

class StraightLine
{
public:
	StraightLine();
	~StraightLine();

	void Point(SDL_Event& mouseEvent, SDL_Renderer* renderer);
	void Draw(SDL_Renderer* renderer);

	std::vector<StraightLine*> lines;

private:
	Vec2* point1;
	Vec2* point2;
};
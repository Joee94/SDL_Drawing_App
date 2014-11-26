#pragma once
#include <SDL.h>
#include <vector>
#include <iostream>
#include "Vec2.h"

class Rectangle
{
public:
	Rectangle();
	~Rectangle();

	void Corner(SDL_Event& mouseEvent, SDL_Renderer* renderer);
	void Draw(SDL_Renderer* renderer);

	std::vector<Rectangle*> rectangles;

private:
	Vec2* corner1;
	Vec2* corner2;
};
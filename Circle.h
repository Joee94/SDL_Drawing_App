#pragma once
#include <SDL.h>
#include <vector>
#include <iostream>
#include "Vec2.h"

class Circle
{
public:
	Circle();
	~Circle();

	void Point(SDL_Event& mouseEvent, SDL_Renderer* renderer);
	void Draw(SDL_Renderer* renderer);

	std::vector<Circle*> lines;

private:
	Vec2* point1;
	Vec2* point2;
	float radius;
	float radiusError;
};
#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include <queue>
#include "Vec2.h"

class Fill
{
public:
	Fill(SDL_Surface *s, SDL_Renderer * renderer, Vec2 pos);
   ~Fill();
   bool checkPixelProcessed(Vec2& n);
   void Draw(SDL_Renderer* renderer, float r, float g, float b, float a);
	unsigned int getpixel(SDL_Surface *s, int x, int y);
	void Colour(uint8_t &red, uint8_t &green, uint8_t &blue, uint8_t &alpha);

   uint8_t GetR();
   uint8_t GetG();
   uint8_t GetB();
   uint8_t GetA();

private:
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
	unsigned int newColour; 
	unsigned int oldColour;
	std::vector<Vec2> points;
};
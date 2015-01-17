#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include <queue>
#include "Vec2.h"
#include "Shape.h"

class Fill : public Shape
{
public:
   Fill(SDL_Surface *s, SDL_Renderer * renderer, Vec2 pos);
   ~Fill();
   bool checkPixelProcessed(Vec2& n);
   void Draw(SDL_Renderer* renderer, float r, float g, float b, float a);
   unsigned int getpixel(SDL_Surface *s, int x, int y);

private:
   int newColour;
   int oldColour;
   int winWidth;
   int winHeight;

};
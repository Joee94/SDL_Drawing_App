#pragma once
#include <SDL.h>
#include <stdint.h>
#include <iostream>
#include "Vec2.h"
#include "Vec3.h"

class Fill
{
public:
   Fill();
   ~Fill();

   uint32_t Fill::getpixel(SDL_Surface* surface, int x, int y);
   Vec2 Point(SDL_Event& mouseEvent);

private:
   Vec2* point;
   SDL_PixelFormat *fmt;
   SDL_Color *colour;
   uint32_t r;
   uint32_t g;
   uint32_t b;
};
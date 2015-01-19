#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include <queue>
#include "Vec2.h"
#include "Shape.h"

/// The Fill class
class Fill : public Shape
{
public:
   /// \brief Fill constructor
   /// \param s surface to write to
   /// \param renderer renderer to write to
   /// \param pos position to start filling
   Fill(SDL_Surface *s, SDL_Renderer * renderer, Vec2 pos);

   ~Fill();

   /// \brief checking whether a pixel has been processed
   /// \param n the pixel to check
   bool checkPixelProcessed(Vec2& n);

   void Draw(SDL_Renderer* renderer, float r, float g, float b, float a);

   /// \brief getting the pixel colour of a pixel
   /// \param s surface to read from
   /// \param x the x co ordinate to read from
   /// \param y the y co ordinate to read from
   unsigned int getpixel(SDL_Surface *s, int x, int y);

private:
   int newColour; ///< The colour you would like to change to
   int oldColour; ///< The colour you are changing from
   int winWidth;  ///< The width of the window
   int winHeight; ///< The height of the window

};
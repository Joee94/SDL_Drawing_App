#include "Fill.h"

Fill::Fill()
{
   point = new Vec2();
}

Fill::~Fill()
{
   delete point;
}

Vec2 Fill::Point(SDL_Event& mouseEvent, SDL_Renderer* renderer)
{
   switch (mouseEvent.type)
   {
   case SDL_MOUSEBUTTONDOWN:
      point->x = mouseEvent.button.x;
      point->y = mouseEvent.button.y;
      return *point;
      break;
   }
}

uint32_t Fill::getpixel(SDL_Surface* surface, int x, int y)
{
   x = point->x;
   y = point->y;
   int bpp = surface->format->BytesPerPixel;
   std::cout << bpp << std::endl;
   /* Here p is the address to the pixel we want to retrieve */
   uint8_t *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

   switch (bpp) {
   case 1:
      std::cout << 1;
      return *p;
      break;

   case 2:
      std::cout << 2;
      return *(Uint16 *)p;
      break;

   case 3:
      std::cout << 3;
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
         return p[0] << 16 | p[1] << 8 | p[2];
      else
         return p[0] | p[1] << 8 | p[2] << 16;
      break;

   case 4:
      return *(Uint32 *)p;
      break;

   default:
      return 0;       /* shouldn't happen, but avoids warnings */
   }
}
#include "Fill.h"

Fill::Fill(SDL_Surface *s, SDL_Renderer * renderer, Vec2 pos)
{
   point1 = new Vec2(pos);
   shapeType = 6;
   newColour = getpixel(s, 275, 25);
   oldColour = getpixel(s, pos.x, pos.y);
   std::queue<Vec2> q;
   SDL_GetRendererOutputSize(renderer, &winWidth, &winHeight);

   if (newColour == oldColour)
   {
      return;
   }

   q.push(pos);
   SDL_Event incomingEvent;
   while (!q.empty())
   {
      Vec2 n = q.front();
      q.pop();


      SDL_PollEvent(&incomingEvent);
      switch (incomingEvent.type)   //Using the type for a case statement
      {
      case SDL_KEYDOWN:
         //Selecting the tools
         switch (incomingEvent.key.keysym.sym)
         {
            //Straight Line
         case SDLK_u:
            std::cout << "test";
            return;
            break;
         }
         break;
      }
      if (n.x >= 0 && n.x <= winWidth && n.y >= 0 && n.y <= winHeight)
      {

         if (getpixel(s, n.x, n.y) == oldColour && (!checkPixelProcessed(Vec2(n.x, n.y))))
         {
            //std::cout << getpixel(s, n.x, n.y) << std::endl;
            points.push_back(n);

            if (!checkPixelProcessed(Vec2(n.x + 1, n.y)))
            {
               q.push(Vec2(n.x + 1, n.y));
            }
            if (!checkPixelProcessed(Vec2(n.x - 1, n.y)))
            {
               q.push(Vec2(n.x - 1, n.y));
            }
            if (!checkPixelProcessed(Vec2(n.x, n.y + 1)))
            {
               q.push(Vec2(n.x, n.y + 1));
            }
            if (!checkPixelProcessed(Vec2(n.x, n.y - 1)))
            {
               q.push(Vec2(n.x, n.y - 1));
            }
         }
      }
   }
}

Fill::~Fill()
{
}


inline bool Fill::checkPixelProcessed(Vec2& n)
{
   bool temp = false;
   //doing a parallel for loop speeds things up ridiculously
#pragma omp parallel for
   for (int i = 0; i < points.size(); ++i)
   {
      if (points[i] == n)
      {
         temp = true;   //parallel for loops don't like returning.
      }
   }

   if (temp == true)
      return true;
   return false;
}

void Fill::Draw(SDL_Renderer* renderer, float r, float g, float b, float a)
{
   SDL_SetRenderDrawColor(renderer, r, g, b, a);
   if (!points.empty())
   {
      for (int i = 0; i < points.size(); ++i)
      {
         SDL_RenderDrawPoint(renderer, points[i].x, points[i].y);
      }
   }
}

inline unsigned int Fill::getpixel(SDL_Surface *s, int x, int y)
{
   return ((unsigned int*)s->pixels)[y*(s->pitch / sizeof(unsigned int)) + x];
}

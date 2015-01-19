#include "Fill.h"

Fill::Fill(SDL_Surface *s, SDL_Renderer * renderer, Vec2 pos)
{
   point1 = new Vec2(pos); //For loading purposes
   shapeType = 6; //Loading/saving purposes
   newColour = getpixel(s, 275, 25);   //The colour we would like it to be
   oldColour = getpixel(s, pos.x, pos.y); //The colour we're looking to change
   std::queue<Vec2> q;  //A queue to store all the pixels to check
   SDL_GetRendererOutputSize(renderer, &winWidth, &winHeight);

   //If the new colour matches the old colour do nothing
   if (newColour == oldColour)
   {
      return;
   }
   
   //add the first position to the queue
   q.push(pos);
   SDL_Event incomingEvent;
   while (!q.empty())
   {
      //set a Vec2 to the front of the queue
      Vec2 n = q.front();
      //Remove that element from the queue
      q.pop();

      SDL_PollEvent(&incomingEvent);
      switch (incomingEvent.type)   //Using the type for a case statement
      {
      case SDL_KEYDOWN:
         //Incase it tries to fill the whole screen you can cancel it
         switch (incomingEvent.key.keysym.sym)
         {
         case SDLK_u:
            return;
            break;
         }
         break;
      }
      //Adapted from http://en.wikipedia.org/wiki/Flood_fill
      //First checking it's inside the window
      if (n.x >= 0 && n.x <= winWidth && n.y >= 0 && n.y <= winHeight)
      {
         // Then checking if the pixel is the colour which needs to be replaces AND 
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

#include "Position.h"
#include <iostream>

Position::Position()
{
   point = new Vec2();
}


Position::~Position()
{
}

Vec2 Position::GetPosition(SDL_Event& mouseEvent)
{
   point->x = mouseEvent.button.x;
   point->y = mouseEvent.button.y;
   return *point;
}

bool Position::CheckPosition(SDL_Event& mouseEvent, Vec2 topleft, Vec2 bottomright)
{
   point->x = mouseEvent.button.x;
   point->y = mouseEvent.button.y;
   std::cout << topleft.x << " " << topleft.y << std::endl;
   std::cout << bottomright.x << " " << bottomright.y << std::endl;
   if (((point->x > topleft.x) && (point->y > topleft.y)) && ((point->x < bottomright.x) && (point->y < bottomright.y)))  //Uhhh is there a better way of doing this?
   {
      std::cout << "yes";
      return 1;
   }
   else
   {
      return 0;
   }

}
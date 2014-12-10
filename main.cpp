#define SLIDER_TL_X 78
#define SLIDER_TL_Y 13
#define SLIDER_BR_X 201
#define SLIDER_BR_Y 26
// This is the main SDL include file
#include <SDL.h>
#include <SDL_Image.h>
// iostream is so we can output error messages to console
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "StraightLine.h"
#include "Rectangle.h"
#include "Circle.h"
#include "CurvedLine.h"
#include "Sprite.h"
#include "Fill.h"
#include "Position.h"

void LoadFile(std::vector<Shape*> &shapes, std::string filename);
void SaveFile(std::vector<Shape*> shapes);
float ColourValue(uint8_t v);

int main(int argc, char *argv[])
{
   if (SDL_Init(SDL_INIT_VIDEO) < 0)
   {
      // Something went very wrong in initialisation, all we can do is exit
      std::cout << "Whoops! Something went very wrong, cannot initialise SDL :(" << std::endl;
      return -1;
   }

   //Setting up the window
   int winPosX = 100;
   int winPosY = 100;
   int winWidth = 640;
   int winHeight = 480;
   SDL_Window *window = SDL_CreateWindow("My Window!!!",  // The first parameter is the window title
      winPosX, winPosY,
      winWidth, winHeight,
      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
   SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
   SDL_Surface* screen;

   unsigned int lastTime = SDL_GetTicks();
   bool go = true;

   //These could all really be on one sprite sheet... bleh maybe later
   Sprite* Sheet = new Sprite;
   Sprite* LineGUI      = new Sprite;
   Sprite* RectangleGUI = new Sprite;
   Sprite* CircleGUI    = new Sprite;
   Sprite* CurvedGUI    = new Sprite;
   Sprite* ColourPicker = new Sprite;
   Sprite* Slider = new Sprite;
   Fill* Bucket = new Fill;
   Position* pos = new Position;

   //My std::vectors, may remove and try and put everything in one Shapes Vector but I'll get to that....
   std::vector<Shape*> shapes;
   std::string dropped_filedir;                  // Pointer for directory of dropped file

   //There MUST be a better way to do this.... I'm just tired
   uint8_t slider_r = 72;
   uint8_t slider_g = 72;
   uint8_t slider_b = 72;

   Vec2* slider_min_r = new Vec2(SLIDER_TL_X, SLIDER_TL_Y);
   Vec2* slider_max_r = new Vec2(SLIDER_BR_X, SLIDER_BR_Y);

   Vec2* slider_min_g = new Vec2(SLIDER_TL_X, SLIDER_TL_Y+32);
   Vec2* slider_max_g = new Vec2(SLIDER_BR_X , SLIDER_BR_Y+32);

   Vec2* slider_min_b = new Vec2(SLIDER_TL_X, SLIDER_TL_Y+64);
   Vec2* slider_max_b = new Vec2(SLIDER_BR_X, SLIDER_BR_Y+64);

   //Loading the line by default until it's changed

   Sheet->LoadFromBMP("spritesheet.png", renderer);
   LineGUI->LoadFromBMP("line.png", renderer);
   RectangleGUI->LoadFromBMP("rectangle.png", renderer);
   CircleGUI->LoadFromBMP("circle.png", renderer);
   CurvedGUI->LoadFromBMP("curved.png", renderer);
   ColourPicker->LoadFromBMP("picker.png", renderer);
   Slider->LoadFromBMP("slider.png", renderer);
   //A selector to choose which tool to use
   int selector = 0;
   //The game loop
   while (go)
   {
      SDL_Event incomingEvent;
      while (SDL_PollEvent(&incomingEvent))  //Checking which event is coming in
      {
         switch (incomingEvent.type)   //Using the type for a case statement
         {
         case SDL_QUIT:
            go = false;
            break;
         case SDL_DROPFILE:
         {
            dropped_filedir = incomingEvent.drop.file;
            LoadFile(shapes, dropped_filedir);
            break;
         }
         case SDL_MOUSEBUTTONDOWN:  //When the user presses the mouse button is will create a new object and add it to a vector
            if (pos->CheckPosition(incomingEvent, *slider_min_r, *slider_max_r))
            {
               slider_r = pos->GetPosition(incomingEvent).x;
            }
            else if (pos->CheckPosition(incomingEvent, *slider_min_g, *slider_max_g))
            {
               slider_g = pos->GetPosition(incomingEvent).x;
            }
            else if (pos->CheckPosition(incomingEvent, *slider_min_b, *slider_max_b))
            {
               slider_b = pos->GetPosition(incomingEvent).x;
            }
            else
            {
               switch (selector)
               {
               case 0:
                  //Straight Line
                  shapes.push_back(new StraightLine());   //Adding to vector
                  shapes.back()->Point(incomingEvent);   //Calling the point function to start plotting the first point
                  shapes.back()->Colour(slider_r, slider_g, slider_b);
                  break;
               case 1:
                  //Rectangle
                  shapes.push_back(new Rectangle());    //etc. etc.
                  shapes.back()->Point(incomingEvent);
                  shapes.back()->Colour(slider_r, slider_g, slider_b);
                  break;
               case 2:
                  //Circle
                  shapes.push_back(new Circle());
                  shapes.back()->Point(incomingEvent);
                  shapes.back()->Colour(slider_r, slider_g, slider_b);
                  break;
               case 3:
                  //Curved Line
                  std::cout << "point1";
                  shapes.push_back(new CurvedLine());
                  shapes.back()->Point(incomingEvent, 0);
                  shapes.back()->Colour(slider_r, slider_g, slider_b);
                  break;
               case 5:
                  //Fill
                  SDL_Surface *surface = SDL_GetWindowSurface(window);
                  Vec2 point = Bucket->Point(incomingEvent);
                  std::cout << Bucket->getpixel(surface, point.x, point.y);
                  break;
               }
            }
            break;
            //Bit of an issue, basically don't drag things into the top left 
         case SDL_MOUSEBUTTONUP:
            switch (selector)
            {
            case 0:
            case 1:
            case 2:
               //Straight Line
               shapes.back()->Point(incomingEvent);   //I then access the same object created before and call Point again for the second point...
               break;
            case 3:
               //Curved Line
               shapes.back()->Point(incomingEvent, 1);
               selector = 4;
               break;
            case 4:
               //Control Point of Curved Line
               std::cout << "point3";
               shapes.back()->Point(incomingEvent, 2);   // Or sometimes the 3rd point based on the shape
               selector = 3;
               break;

            }
            break;
         case SDL_KEYDOWN:
            //Selecting the tools, might change this
            switch (incomingEvent.key.keysym.sym)
            {

            case SDLK_1:
               selector = 0;
               break;
            case SDLK_2:
               selector = 1;
               break;
            case SDLK_3:
               selector = 2;
               break;
            case SDLK_4:
               selector = 3;
               break;
            case SDLK_5:
               selector = 5;
               break;
            case SDLK_s:
               SaveFile(shapes);
            }
            break;
         }
      }


      unsigned int current = SDL_GetTicks();
      float deltaTs = (float)(current - lastTime) / 1000.0f;
      // Now that we've done this we can use the current time as the next frame's previous time
      lastTime = current;


      // Start by clearing what was drawn before
      // Set the colour for drawing
      SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
      // Clear the entire screen to our selected colour
      SDL_RenderClear(renderer);


      //Hooray, one single loop to draw everything :o)
      if (!shapes.empty())
      {
         for (uint32_t i = 0; i < shapes.size(); ++i)
         {
            shapes[i]->Draw(renderer, ColourValue(shapes[i]->GetR() - 72), ColourValue(shapes[i]->GetG() - 72), ColourValue(shapes[i]->GetB() - 72));

         }
      }

      //Drawing the GUI
      ColourPicker->Draw(50, 0, renderer);
      Slider->Draw(slider_r, 10, renderer);
      Slider->Draw(slider_g, 41, renderer);
      Slider->Draw(slider_b, 72, renderer);

      switch (selector)
      {
      case 0:
         LineGUI->Draw(0, 0, renderer);
         break;
      case 1:
         RectangleGUI->Draw(0, 0, renderer);
         break;
      case 2:
         CircleGUI->Draw(0, 0, renderer);
         break;
      case 3:
      case 4:
         CurvedGUI->Draw(0, 0, renderer);
         break;

      }

      //Just a little rectangle to show what colour is selected
      SDL_Rect colour = { 250, 0, 50, 50};
      SDL_SetRenderDrawColor(renderer, ColourValue(slider_r - 72), ColourValue(slider_g - 72), ColourValue(slider_b - 72), 0xFF);
      SDL_RenderFillRect(renderer, &colour);


      // This tells the renderer to actually show its contents to the screen
      // We'll get into this sort of thing at a later date - or just look up 'double buffering' if you're impatient :P
      SDL_RenderPresent(renderer);


      // Limiter in case we're running really quick
      if (deltaTs < (1.0f / 50.0f))	// not sure how accurate the SDL_Delay function is..
      {
         SDL_Delay((unsigned int)(((1.0f / 50.0f) - deltaTs)*1000.0f));
      }

   }
   // If we get outside the main game loop, it means our user has requested we exit


   // Our cleanup phase, hopefully fairly self-explanatory ;)
   SDL_DestroyWindow(window);
   SDL_Quit();

   return 0;
}

void LoadFile(std::vector<Shape*> &shapes, std::string filename)
{

   //Blech this wasn't fun
   std::ifstream saveData(filename);   //m'file
   std::string currentLine;   //m'line
   std::vector<int> types;  //m'types

   while (std::getline(saveData, currentLine))  //Are there lines?
   {
      std::stringstream linestream(currentLine);   //YES THERE ARE
      int type;    //The type of shape we gon' draw
      float x0, y0, x1, y1, x2, y2;   //bunch of co-ordinates

      linestream >> type >> x0 >> y0 >> x1 >> y1 >> x2 >> y2; //then just get the rest

      //eh I couldn't do a case statement for strings, I probably shoudl just use ints.... maybe if I can be assed in the future.
      switch (type)
      {
      case 0:
         shapes.push_back(new StraightLine());
         shapes.back()->Point(x0, y0, x1, y1);
         break;
      case 1:
         shapes.push_back(new Rectangle());
         shapes.back()->Point(x0, y0, x1, y1);
         break;
      case 2:
         shapes.push_back(new Circle());
         shapes.back()->Point(x0, y0, x1, y1);
         break;
      case 3:
         shapes.push_back(new CurvedLine());
         shapes.back()->Point(x0, y0, x1, y1, x2, y2);
         break;
      }
      types.push_back(type);  //add it to some types array for later
   }


   saveData.close();

}

void SaveFile(std::vector<Shape*> shapes)
{
   FILE *f;
   errno_t err;

   if ((err = fopen_s(&f, "savedata.joe", "w")) != 0)
   {
      std::cout << "Error, file not found";
   }
   else
   {
      if (!shapes.empty())
      {
         for (uint32_t i = 0; i < shapes.size(); ++i)
         {
            if (shapes[i]->GetShapeType() != 3)
            {
               fprintf(f, "%i\t%f\t%f\t%f\t%f\t%f\t%f\n",      //So... this is where all the stuff is output to a text doc, issues with the control point meant
                  shapes[i]->GetShapeType(),                   //I had to split this up into shapes with 2 points and shapes with 3... bleh I tried other methods
                  shapes[i]->GetPoint1().x,                    //but nothing worked :( (Still shorter than my last attempt)
                  shapes[i]->GetPoint1().y,
                  shapes[i]->GetPoint2().x,
                  shapes[i]->GetPoint2().y);
            }
            else
            {
               fprintf(f, "%i\t%f\t%f\t%f\t%f\t%f\t%f\n",
                  shapes[i]->GetShapeType(),
                  shapes[i]->GetPoint1().x,
                  shapes[i]->GetPoint1().y,
                  shapes[i]->GetPoint2().x,
                  shapes[i]->GetPoint2().y,
                  shapes[i]->GetControlPoint().x,
                  shapes[i]->GetControlPoint().y);
            }
         }
      }
      fclose(f);
   }
}

float ColourValue(uint8_t v)
{
   v = v * 2;
   return v;
}
#define SLIDER_TL_X 78
#define SLIDER_TL_Y 9
#define SLIDER_BR_X 201
#define SLIDER_BR_Y 23
// This is the main SDL include file
#include <SDL.h>
#include <SDL_Image.h>
// iostream is so we can output error messages to console
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <thread>
#include "StraightLine.h"
#include "Rectangle.h"
#include "Circle.h"
#include "CurvedLine.h"
#include "CurvedLine2.h"
#include "Sprite.h"
#include "Fill.h"
#include "Position.h"

void LoadFile(std::vector<Shape*> &shapes, std::string filename);
void SaveFile(std::vector<Shape*> shapes);
float ColourValue(uint8_t v);

struct Colour{
   uint8_t  red = 0;
   uint8_t  green = 0;
   uint8_t  blue = 0;
   uint8_t  alpha = 255;
};

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

   unsigned int lastTime = SDL_GetTicks();
   bool go = true;

   Colour *colour = new Colour;
   Colour *bgCol = new Colour;

   //These could all really be on one sprite sheet... bleh maybe later
   Sprite* Sheet = new Sprite;
   Sprite* LineGUI = new Sprite;
   Sprite* RectangleGUI = new Sprite;
   Sprite* CircleGUI = new Sprite;
   Sprite* CurvedGUI = new Sprite;
   Sprite* Curved2GUI = new Sprite;
   Sprite* ColourPicker = new Sprite;
   Sprite* Slider = new Sprite;
   Sprite* Transparent = new Sprite;
   Position* pos = new Position;

   //My std::vectors, may remove and try and put everything in one Shapes Vector but I'll get to that....
   std::vector<Shape*> shapes;
   std::string dropped_filedir;                  // Pointer for directory of dropped file

   //There MUST be a better way to do this.... I'm just tired
   uint8_t slider_r = 72;
   uint8_t slider_g = 72;
   uint8_t slider_b = 72;
   uint8_t slider_a = 72;

   Vec2* slider_min_r = new Vec2(SLIDER_TL_X, SLIDER_TL_Y);
   Vec2* slider_max_r = new Vec2(SLIDER_BR_X, SLIDER_BR_Y);

   Vec2* slider_min_g = new Vec2(SLIDER_TL_X, SLIDER_TL_Y + 30);
   Vec2* slider_max_g = new Vec2(SLIDER_BR_X, SLIDER_BR_Y + 30);

   Vec2* slider_min_b = new Vec2(SLIDER_TL_X, SLIDER_TL_Y + 58);
   Vec2* slider_max_b = new Vec2(SLIDER_BR_X, SLIDER_BR_Y + 58);

   Vec2* slider_min_a = new Vec2(SLIDER_TL_X, SLIDER_TL_Y + 87);
   Vec2* slider_max_a = new Vec2(SLIDER_BR_X, SLIDER_BR_Y + 87);

   Vec2* GUITopLeft = new Vec2(50.0f, 0);
   Vec2* GUIBottomRight = new Vec2(250.0f, 120.0f);

   Vec2* toolPicker = new Vec2(50.0f, 250.0f);

   //Loading the line by default until it's changed

   Sheet->LoadFromBMP("spritesheet.png", renderer);
   LineGUI->LoadFromBMP("line.png", renderer);
   RectangleGUI->LoadFromBMP("rectangle.png", renderer);
   CircleGUI->LoadFromBMP("circle.png", renderer);
   CurvedGUI->LoadFromBMP("curved.png", renderer);
   Curved2GUI->LoadFromBMP("cubecurve.png", renderer);
   ColourPicker->LoadFromBMP("picker.png", renderer);
   Slider->LoadFromBMP("slider.png", renderer);
   Transparent->LoadFromBMP("transparent.png", renderer);
   //A selector to choose which tool to use
   int selector = 0;
   //The game loop
   SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
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
            //std::thread f(LoadFile, shapes, dropped_filedir);#
            LoadFile(shapes, dropped_filedir);
            //f.detach();
            break;
         }
         case SDL_MOUSEBUTTONDOWN:  //When the user presses the mouse button is will create a new object and add it to a vector
            //currently doesn't work
            //glReadPixels(incomingEvent.button.x, incomingEvent.button.y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixel);
            //std::cout << (int)pixel.red << " " << (int)pixel.green << " " << (int)pixel.blue << "test" << std::endl;
            if (pos->CheckPosition(incomingEvent, *GUITopLeft, *GUIBottomRight))
            {
               if (pos->CheckPosition(incomingEvent, *slider_min_r, *slider_max_r))
               {
                  slider_r = pos->GetPosition(incomingEvent).x - 5;
                  colour->red = slider_r - 72;
               }
               else if (pos->CheckPosition(incomingEvent, *slider_min_g, *slider_max_g))
               {
                  slider_g = pos->GetPosition(incomingEvent).x - 5;
                  colour->green = slider_g - 72;
               }
               else if (pos->CheckPosition(incomingEvent, *slider_min_b, *slider_max_b))
               {
                  slider_b = pos->GetPosition(incomingEvent).x - 5;
                  colour->blue = slider_b - 72;
               }
               else if (pos->CheckPosition(incomingEvent, *slider_min_a, *slider_max_a))
               {
                  slider_a = pos->GetPosition(incomingEvent).x - 5;
                  colour->alpha = slider_a - 72;
               }
            }
            if (pos->CheckPosition(incomingEvent, 0, *toolPicker))
            {
               if (pos->CheckPosition(incomingEvent, 0, 50))
               {
                  selector = 0;
               }
               else if (pos->CheckPosition(incomingEvent, Vec2(0, 50), Vec2(50, 100)))
               {
                  selector = 1;
               }
               else if (pos->CheckPosition(incomingEvent, Vec2(0, 100), Vec2(50, 150)))
               {
                  selector = 2;
               }
               else if (pos->CheckPosition(incomingEvent, Vec2(0, 150), Vec2(50, 200)))
               {
                  selector = 3;
               }
               else if (pos->CheckPosition(incomingEvent, Vec2(0, 200), Vec2(50, 250)))
               {
                  selector = 3;
               }
            }
            else
            {
               switch (selector)
               {
               case 0:
                  //Straight Line
                  shapes.push_back(new StraightLine());   //Adding to vector
                  shapes.back()->Point(incomingEvent);   //Calling the point function to start plotting the first point
                  shapes.back()->Colour(colour->red, colour->green, colour->blue, colour->alpha);
                  break;
               case 1:
                  //Rectangle
                  shapes.push_back(new Rectangle());    //etc. etc.
                  shapes.back()->Point(incomingEvent);
                  shapes.back()->Colour(colour->red, colour->green, colour->blue, colour->alpha);
                  break;
               case 2:
                  //Circle
                  shapes.push_back(new Circle());
                  shapes.back()->Point(incomingEvent);
                  shapes.back()->Colour(colour->red, colour->green, colour->blue, colour->alpha);
                  break;
               case 3:
                  //Curved Line
                  shapes.push_back(new CurvedLine());
                  shapes.back()->Point(incomingEvent, 0);
                  shapes.back()->Colour(colour->red, colour->green, colour->blue, colour->alpha);
                  break;
               case 5:
                  //Curved Line 2
                  shapes.push_back(new CurvedLine2());
                  shapes.back()->Point(incomingEvent, 0);
                  shapes.back()->Colour(colour->red, colour->green, colour->blue, colour->alpha);
                  break;

               }
            }
            break;
         case SDL_MOUSEBUTTONUP:
            if (!pos->CheckPosition(incomingEvent, *GUITopLeft, *GUIBottomRight))
            {
               if (!pos->CheckPosition(incomingEvent, 0, *toolPicker))
               {
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
                     shapes.back()->Point(incomingEvent, 2);   // Or sometimes the 3rd point based on the shape
                     selector = 3;
                     break;

                  case 5:
                     //Curved Line 2
                     shapes.back()->Point(incomingEvent, 1);  
                     selector = 6;
                     break;
                  case 6:
                     //Control Point 1 Curved Line 2
                     shapes.back()->Point(incomingEvent, 2);  
                     selector = 7;
                     break;
                  case 7:
                     //Control Point 2 of Curved Line 2
                     shapes.back()->Point(incomingEvent, 3);  
                     selector = 5;
                     break;
                  }
               }
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
               break;
            case SDLK_b:
               bgCol->red = ColourValue(colour->red);
               bgCol->green = ColourValue(colour->green);
               bgCol->blue = ColourValue(colour->blue);
               bgCol->alpha = ColourValue(colour->alpha);
               break;
            }
            break;
         }
      }
      //Setting the alpha blendmode
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);


      unsigned int current = SDL_GetTicks();
      float deltaTs = (float)(current - lastTime) / 1000.0f;
      // Now that we've done this we can use the current time as the next frame's previous time
      lastTime = current;


      // Start by clearing what was drawn before
      // Set the colour for drawing
      SDL_SetRenderDrawColor(renderer, bgCol->red, bgCol->green, bgCol->blue, bgCol->alpha);
      // Clear the entire screen to our selected colour
      SDL_RenderClear(renderer);


      //Hooray, one single loop to draw everything :o)
      if (!shapes.empty())
      {
         #pragma omp parallel for
         for (uint32_t i = 0; i < shapes.size(); ++i)
         {
            shapes[i]->Draw(renderer, ColourValue(shapes[i]->GetR()), ColourValue(shapes[i]->GetG()), ColourValue(shapes[i]->GetB()), ColourValue(shapes[i]->GetA()));
         }
      }

      //Drawing the GUI
      ColourPicker->Draw(50, 0, renderer);
      Slider->Draw(slider_r, 6, renderer);
      Slider->Draw(slider_g, 36, renderer);
      Slider->Draw(slider_b, 64, renderer);
      Slider->Draw(slider_a, 93, renderer);
      Transparent->Draw(250, 0, renderer);

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
      case 5:
      case 6:
      case 7:
         Curved2GUI->Draw(0, 0, renderer);
         break;

      }

      //Just a little rectangle to show what colour is selected
      SDL_Rect currentColour = { 250, 0, 50, 50 };
      SDL_SetRenderDrawColor(renderer, ColourValue(colour->red), ColourValue(colour->green), ColourValue(colour->blue), ColourValue(colour->alpha));
      SDL_RenderFillRect(renderer, &currentColour);


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
      float x0, y0, x1, y1, x2, y2, x3, y3;   //bunch of co-ordinates
      uint8_t r, g, b, a;

      linestream >> type >> x0 >> y0 >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> r >> g >> b >> a; //then just get the rest

      //eh I couldn't do a case statement for strings, I probably shoudl just use ints.... maybe if I can be assed in the future.
      switch (type)
      {
      case 0:
         shapes.push_back(new StraightLine());
         shapes.back()->Point(x0, y0, x1, y1);
         shapes.back()->Colour(r, g, b, a);
         break;
      case 1:
         shapes.push_back(new Rectangle());
         shapes.back()->Point(x0, y0, x1, y1);
         shapes.back()->Colour(r, g, b, a);
         break;
      case 2:
         shapes.push_back(new Circle());
         shapes.back()->Point(x0, y0, x1, y1);
         shapes.back()->Colour(r, g, b, a);
         break;
      case 3:
         shapes.push_back(new CurvedLine());
         shapes.back()->Point(x0, y0, x1, y1, x2, y2);
         shapes.back()->Colour(r, g, b, a);
         break;
      case 4:
         shapes.push_back(new CurvedLine2());
         shapes.back()->Point(x0, y0, x1, y1, x2, y2, x3, y3);
         shapes.back()->Colour(r, g, b, a);
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
            if (shapes[i]->GetShapeType() < 3)
            {
               fprintf(f, "%i\t%f\t%f\t%f\t%f\t%i\t%i\t%i\t%i\n",
                  shapes[i]->GetShapeType(),
                  shapes[i]->GetPoint1().x,
                  shapes[i]->GetPoint1().y,
                  shapes[i]->GetPoint2().x,
                  shapes[i]->GetPoint2().y,
                  shapes[i]->GetR(),
                  shapes[i]->GetG(),
                  shapes[i]->GetB(),
                  shapes[i]->GetA());
            }
            else if (shapes[i]->GetShapeType() == 3)
            {
               fprintf(f, "%i\t%f\t%f\t%f\t%f\t%f\t%f\t%i\t%i\t%i\t%i\n",
                  shapes[i]->GetShapeType(),
                  shapes[i]->GetPoint1().x,
                  shapes[i]->GetPoint1().y,
                  shapes[i]->GetPoint2().x,
                  shapes[i]->GetPoint2().y,
                  shapes[i]->GetControlPoint().x,
                  shapes[i]->GetControlPoint().y,
                  shapes[i]->GetR(),
                  shapes[i]->GetG(),
                  shapes[i]->GetB(),
                  shapes[i]->GetA());
            }
            else
            {
               fprintf(f, "%i\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%i\t%i\t%i\t%i\n",
                  shapes[i]->GetShapeType(),
                  shapes[i]->GetPoint1().x,
                  shapes[i]->GetPoint1().y,
                  shapes[i]->GetPoint2().x,
                  shapes[i]->GetPoint2().y,
                  shapes[i]->GetControlPoint().x,
                  shapes[i]->GetControlPoint().y,
                  shapes[i]->GetControlPoint2().x,
                  shapes[i]->GetControlPoint2().y,
                  shapes[i]->GetR(),
                  shapes[i]->GetG(),
                  shapes[i]->GetB(),
                  shapes[i]->GetA());
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
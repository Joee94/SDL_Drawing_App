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
#include <queue>
#include <ctime>
#include "StraightLine.h"
#include "Rectangle.h"
#include "Circle.h"
#include "CurvedLine.h"
#include "CurvedLine2.h"
#include "Triangle.h"
#include "Sprite.h"
#include "Fill.h"
#include "Position.h"

/// declares a type called 'Colour'
struct Colour
{
   uint8_t  red = 0;     ///< the red colour
   uint8_t  green = 0;   ///< the green colour
   uint8_t  blue = 0;    ///< the blue colour
   uint8_t  alpha = 255; ///< the alpha value
};

void LoadFile(std::vector<Shape*> &shapes, std::string filename, SDL_Surface* s, SDL_Renderer* renderer);
void SaveFile(std::vector<Shape*> shapes, Colour *bgColour, std::string file);
float ColourValue(uint8_t v);
void fill(SDL_Surface *s, SDL_Renderer * renderer, Vec2 pos, unsigned int newColour, unsigned int oldColour);
bool checkPixelProcessed(Vec2& n);
inline unsigned int getpixel(SDL_Surface *s, int x, int y);

//I'm sorry for the global... I just could not get it to work without
Colour *bgCol = new Colour;

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
   SDL_Window *window = SDL_CreateWindow("MSPaint",  // The first parameter is the window title
      winPosX, winPosY,
      winWidth, winHeight,
      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
   SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

   unsigned int lastTime = SDL_GetTicks();
   bool go = true;

   Colour *colour = new Colour;

   //These could all really be on one sprite sheet... bleh maybe later
   Sprite* LineGUI = new Sprite;
   Sprite* RectangleGUI = new Sprite;
   Sprite* CircleGUI = new Sprite;
   Sprite* CurvedGUI = new Sprite;
   Sprite* Curved2GUI = new Sprite;
   Sprite* TriangleGUI = new Sprite;
   Sprite* FillGUI = new Sprite;
   Sprite* PickerGUI = new Sprite;
   Sprite* ColourPicker = new Sprite;
   Sprite* Slider = new Sprite;
   Sprite* Transparent = new Sprite;
   Position* pos = new Position;

   LineGUI->LoadFromBMP("line.png", renderer);
   RectangleGUI->LoadFromBMP("rectangle.png", renderer);
   CircleGUI->LoadFromBMP("circle.png", renderer);
   CurvedGUI->LoadFromBMP("curved.png", renderer);
   Curved2GUI->LoadFromBMP("cubecurve.png", renderer);
   TriangleGUI->LoadFromBMP("triangle.png", renderer);
   FillGUI->LoadFromBMP("fill.png", renderer);
   PickerGUI->LoadFromBMP("colourpicker.png", renderer);   //This colour picker naming stuff is confusing...
   ColourPicker->LoadFromBMP("picker.png", renderer);
   Slider->LoadFromBMP("slider.png", renderer);
   Transparent->LoadFromBMP("transparent.png", renderer);

   //My std::vectors, may remove and try and put everything in one Shapes Vector but I'll get to that....
   std::vector<Shape*> shapes;
   std::string dropped_filedir = "savedata.joe";                  // Pointer for directory of dropped file

   //There MUST be a better way to do this.... I'm just tired
   uint8_t slider_r = 72;
   uint8_t slider_g = 72;
   uint8_t slider_b = 72;
   uint8_t slider_a = 201;

   Vec2* GUITopLeft = new Vec2(50.0f, 0);
   Vec2* GUIBottomRight = new Vec2(250.0f, 120.0f);

   Vec2* toolPicker = new Vec2(50.0f, 400.0f);

   //Loading the line by default until it's changed


   SDL_Surface *sshot;
   SDL_Surface *s;
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
            SDL_GetRendererOutputSize(renderer, &winWidth, &winHeight);
            s = SDL_CreateRGBSurface(0, winWidth, winHeight, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
            SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, s->pixels, s->pitch);
            LoadFile(shapes, dropped_filedir, s, renderer);
            break;
         }
         case SDL_MOUSEBUTTONDOWN:  //When the user presses the mouse button is will create a new object and add it to a vector
            //currently doesn't work
            //glReadPixels(incomingEvent.button.x, incomingEvent.button.y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixel);
            //std::cout << (int)pixel.red << " " << (int)pixel.green << " " << (int)pixel.blue << "test" << std::endl;

            //This horrible bit of code checks if you're clicking a slider.
            std::cout << incomingEvent.button.x << std::endl;
            std::cout << incomingEvent.button.y << std::endl;
            if (pos->CheckPosition(incomingEvent, *GUITopLeft, *GUIBottomRight))
            {
               if (pos->CheckPosition(incomingEvent, Vec2(SLIDER_TL_X, SLIDER_TL_Y), Vec2(SLIDER_BR_X, SLIDER_BR_Y)))
               {
                  slider_r = pos->GetPosition(incomingEvent).x - 5;
                  colour->red = slider_r - 72;
               }
               else if (pos->CheckPosition(incomingEvent, Vec2(SLIDER_TL_X, SLIDER_TL_Y + 30), Vec2(SLIDER_BR_X, SLIDER_BR_Y + 30)))
               {
                  slider_g = pos->GetPosition(incomingEvent).x - 5;
                  colour->green = slider_g - 72;
               }
               else if (pos->CheckPosition(incomingEvent, Vec2(SLIDER_TL_X, SLIDER_TL_Y + 58), Vec2(SLIDER_BR_X, SLIDER_BR_Y + 58)))
               {
                  slider_b = pos->GetPosition(incomingEvent).x - 5;
                  colour->blue = slider_b - 72;
               }
               else if (pos->CheckPosition(incomingEvent, Vec2(SLIDER_TL_X, SLIDER_TL_Y + 87), Vec2(SLIDER_BR_X, SLIDER_BR_Y + 87)))
               {
                  slider_a = pos->GetPosition(incomingEvent).x - 5;
                  colour->alpha = slider_a - 72;
               }
            }
            //This part checks which tool is selected
            if (pos->CheckPosition(incomingEvent, 0, *toolPicker))
            {
               if (pos->CheckPosition(incomingEvent, 0, 50))
               {
                  //Straight Line
                  selector = 0;
               }
               else if (pos->CheckPosition(incomingEvent, Vec2(0, 50), Vec2(50, 100)))
               {
                  //Rectangle
                  selector = 1;
               }
               else if (pos->CheckPosition(incomingEvent, Vec2(0, 100), Vec2(50, 150)))
               {
                  //Circle
                  selector = 2;
               }
               else if (pos->CheckPosition(incomingEvent, Vec2(0, 150), Vec2(50, 200)))
               {
                  //Quadratic Curve
                  selector = 3;
               }
               else if (pos->CheckPosition(incomingEvent, Vec2(0, 200), Vec2(50, 250)))
               {
                  //Cubic Curve
                  selector = 5;
               }
               else if (pos->CheckPosition(incomingEvent, Vec2(0, 250), Vec2(50, 300)))
               {
                  //Triangle
                  selector = 8;
               }
               else if (pos->CheckPosition(incomingEvent, Vec2(0, 300), Vec2(50, 350)))
               {
                  //Fill
                  selector = 11;
               }
               else if (pos->CheckPosition(incomingEvent, Vec2(0, 350), Vec2(50, 400)))
               {
                  //Colour Picker
                  selector = 12;
               }
            }
            //This is actually adding the shape to the array
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
               case 11:
                  //Finally discovered how to access a pixels fill colour, credit to http://sdl.5483.n7.nabble.com/Getting-pixel-color-value-at-x-y-from-an-SDL-Surface-td20671.html
                  // for the function and to http://www.gamedev.net/topic/291015-cannot-convert-from-uint32-to-sdl_color/ for converting from a Uint32 to a colour
                  double seconds;
                  time_t now;
                  time(&now);
                  SDL_GetRendererOutputSize(renderer, &winWidth, &winHeight);
                  s = SDL_CreateRGBSurface(0, winWidth, winHeight, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
                  SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, s->pixels, s->pitch);
                  shapes.push_back(new Fill(s, renderer, Vec2((int)incomingEvent.button.x, (int)incomingEvent.button.y)));
                  shapes.back()->Colour(colour->red, colour->green, colour->blue, colour->alpha);
                  time_t end;
                  time(&end);
                  seconds = difftime(end, now);
                  std::cout << "time: " << seconds << std::endl;
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
                  case 8:
                     //Triangle
                     shapes.push_back(new Triangle());
                     shapes.back()->Point(incomingEvent, 0);
                     shapes.back()->Colour(colour->red, colour->green, colour->blue, colour->alpha);
                     selector = 9;
                     break;
                  case 9:
                     //Corner 1 of triangle
                     shapes.back()->Point(incomingEvent, 1);
                     selector = 10;
                     break;
                  case 10:
                     //Corner 2 of triangle
                     shapes.back()->Point(incomingEvent, 2);
                     selector = 8;
                     break;
                  case 12:
                     //Colour Picker
                     SDL_GetRendererOutputSize(renderer, &winWidth, &winHeight);
                     s = SDL_CreateRGBSurface(0, winWidth, winHeight, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
                     SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, s->pixels, s->pitch);
                     std::cout << getpixel(s, incomingEvent.button.x, incomingEvent.button.y) << std::endl;
                     SDL_GetRGBA(getpixel(s, incomingEvent.button.x, incomingEvent.button.y), s->format, &colour->red, &colour->green, &colour->blue, &colour->alpha);
                     break;
                  }
               }
            }
            break;
         case SDL_KEYDOWN:
            //Selecting the tools
            switch (incomingEvent.key.keysym.sym)
            {
               //Straight Line
            case SDLK_1:
               selector = 0;
               break;
               //Rectangle
            case SDLK_2:
               selector = 1;
               break;
               //Circle
            case SDLK_3:
               selector = 2;
               break;
               //Quadratic Curve
            case SDLK_4:
               selector = 3;
               break;
               //Cubic Curve
            case SDLK_5:
               selector = 5;
               break;
               //Triangle
            case SDLK_6:
               selector = 8;
               break;
               //Colour picker
            case SDLK_7:
               selector = 11;
               break;
               //Colour picker
            case SDLK_8:
               selector = 12;
               break;
               //Save File
            case SDLK_s:
               SaveFile(shapes, bgCol, dropped_filedir);
               break;
               //Save Image
            case SDLK_p:
               //Code stolen from http://stackoverflow.com/questions/22315980/sdl2-c-taking-a-screenshot
               SDL_GetRendererOutputSize(renderer, &winWidth, &winHeight);
               sshot = SDL_CreateRGBSurface(0, winWidth, winHeight, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
               SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
               SDL_SaveBMP(sshot, "screenshot.bmp");
               SDL_FreeSurface(sshot);
               break;
               //Change Background Colour
            case SDLK_b:
               bgCol->red = ColourValue(colour->red);
               bgCol->green = ColourValue(colour->green);
               bgCol->blue = ColourValue(colour->blue);
               bgCol->alpha = ColourValue(colour->alpha);
               break;
               //Uno
            case SDLK_z:
               if (!shapes.empty())
                  shapes.pop_back();
               break;
               //Clear Screen
            case SDLK_DELETE:
               if (!shapes.empty())
                  shapes.clear();
               break;
            }
            break;
         }//Switch Incoming Event end
      }//While Incoming Event end
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
         for (int i = 0; i < shapes.size(); ++i)
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
      case 8:
      case 9:
      case 10:
         TriangleGUI->Draw(0, 0, renderer);
         break;
      case 11:
         FillGUI->Draw(0, 0, renderer);
         break;
      case 12:
         PickerGUI->Draw(0, 0, renderer);
         break;


      }
      //std::cout << deltaTs <<std::endl;

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

   }//Loop end
   // If we get outside the main game loop, it means our user has requested we exit


   // Our cleanup phase, hopefully fairly self-explanatory ;)
   SDL_DestroyWindow(window);
   SDL_Quit();

   return 0;
}

/// \brief Loads a file
void LoadFile(std::vector<Shape*> &shapes, std::string filename, SDL_Surface* s, SDL_Renderer* renderer)
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
      float r0, g0, b0, a0;
      uint8_t r, g, b, a;

      linestream >> type >> x0 >> y0 >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> r0 >> g0 >> b0 >> a0; //then just get the rest
      std::cout << type << " " << r0 << " " << g0 << " " << b0 << " " << a0 << std::endl;
      //a bit hacky but it works
      r = r0;
      g = g0;
      b = b0;
      a = a0;
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
      case 5:
         shapes.push_back(new Triangle());
         shapes.back()->Point(x0, y0, x1, y1, x2, y2);
         shapes.back()->Colour(r, g, b, a);
         break;
      case 9:
		  bgCol->red = r;
		  bgCol->green = g;
		  bgCol->blue = b;
		  bgCol->alpha = a;
        break;
      }
      types.push_back(type);  //add it to some types array for later
   }


   saveData.close();

}

/// \brief Saves all the shapesd background colour to file
void SaveFile(std::vector<Shape*> shapes, Colour *bgColour, std::string file)
{
   //converting the string to a char so it can be accessed
   char *cstr = &file[0];

   FILE *f;
   errno_t err;

   if ((err = fopen_s(&f, cstr, "w")) != 0)
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
               //Saving all the normal shapes
               fprintf(f, "%i\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%i\t%i\t%i\t%i\n",
                  shapes[i]->GetShapeType(),
                  shapes[i]->GetPoint1().x,
                  shapes[i]->GetPoint1().y,
                  shapes[i]->GetPoint2().x,
                  shapes[i]->GetPoint2().y,
                  0.0f, 0.0f, 0.0f, 0.0f,
                  shapes[i]->GetR(),
                  shapes[i]->GetG(),
                  shapes[i]->GetB(),
                  shapes[i]->GetA());
            }
            else if (shapes[i]->GetShapeType() == 3 || shapes[i]->GetShapeType() == 5)
            {
               //saving Quadratic curves
               fprintf(f, "%i\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%i\t%i\t%i\t%i\n",
                  shapes[i]->GetShapeType(),
                  shapes[i]->GetPoint1().x,
                  shapes[i]->GetPoint1().y,
                  shapes[i]->GetPoint2().x,
                  shapes[i]->GetPoint2().y,
                  shapes[i]->GetControlPoint().x,
                  shapes[i]->GetControlPoint().y,
                  0.0f, 0.0f,
                  shapes[i]->GetR(),
                  shapes[i]->GetG(),
                  shapes[i]->GetB(),
                  shapes[i]->GetA());
            }
            else if (shapes[i]->GetShapeType() == 4)
            {
               //Saving all the normal shapes
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
            else if (shapes[i]->GetShapeType() == 6)
            {
               //Saving all the normal shapes
               fprintf(f, "%i\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%i\t%i\t%i\t%i\n",
                  shapes[i]->GetShapeType(),
                  shapes[i]->GetPoint1().x,
                  shapes[i]->GetPoint1().y,
                  0.0f, 0.0f, 0.0f, 0.0f,0.0f,0.0f,
                  shapes[i]->GetR(),
                  shapes[i]->GetG(),
                  shapes[i]->GetB(),
                  shapes[i]->GetA());
            }
         }
      }
      fprintf(f, "%i\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%i\t%i\t%i\t%i\n",
         9,
         0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         bgColour->red,
         bgColour->green,
         bgColour->blue,
         bgColour->alpha);
      fclose(f);
   }

}

/// \brief The colour isnt correct untli it is multiplied by 2
float ColourValue(uint8_t v)
{
   v *= 2;
   return v;
}

/// \brief gets the colour from a specific pixel
inline unsigned int getpixel(SDL_Surface *s, int x, int y)
{
   return ((unsigned int*)s->pixels)[y*(s->pitch / sizeof(unsigned int)) + x];
}


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

   Sprite* GUI = new Sprite;
   Fill* Bucket = new Fill;

   //My std::vectors, may remove and try and put everything in one Shapes Vector but I'll get to that....
   std::vector<Shape*> shapes;

   //A selector to choose which tool to use
   int selector = 0;

   //Loading the line by default until it's changed
   GUI->LoadFromBMP("line.png", renderer);

   //Blech this wasn't fun
   FILE *f;
   errno_t err;

   std::ifstream saveData("savedata.txt");   //m'file
   std::string currentLine;   //m'line
   std::vector<int> types;  //m'types
   
   while (std::getline(saveData, currentLine))  //Are there lines?
   {
      std::stringstream linestream(currentLine);   //YES THERE ARE
      int type;    //The type of shape we gon' draw
      float x0;   //bunch of co-ordinates
      float y0;
      float x1;
      float y1;
      float x2;
      float y2;
   
   
      linestream >> type >> x0 >> y0 >> x1 >> y1 >> x2 >> y2; //then just get the rest
      std::cout << type << " " << x0 << " " << y0 << " " << x1 << " " << y1 << " " << x2 << " " << y2 << std::endl;    //debugging mostly
      
      //eh I couldn't do a case statement for strings, I probably shoudl just use ints.... maybe if I can be assed in the future.
      switch (type)
      {
      case 0:
         shapes.push_back(new StraightLine());
         shapes.back()->Point(renderer, x0, y0, x1, y1);
         break;
      case 1:
         shapes.push_back(new Rectangle());
         shapes.back()->Point(renderer, x0, y0, x1, y1);
         break;
      case 2:
         shapes.push_back(new Circle());
         shapes.back()->Point(renderer, x0, y0, x1, y1);
         break;
      case 3:
         shapes.push_back(new CurvedLine());
         shapes.back()->Point(renderer, x0, y0, x1, y1, x2, y2);
         break;
      }
      types.push_back(type);  //add it to some types array for later
   }


   saveData.close();

   //Set text color as black 
   SDL_Color textColor = { 0, 0, 0, 0xFF }; 
   //The current input text. 
   std::string inputText = "Some Text"; 
//   gInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor ); 
   //Enable text input 
   SDL_StartTextInput();

   //The game loop
   while (go)
   {
      //Selecting the correct image to load based on what is selected, seemed more efficient to load 1 image at a time rather than 4 and swapping one out each time... not sure
      switch (selector)
      {
      case 0:
         //Straight Line
         GUI->LoadFromBMP("line.png", renderer);
         break;
      case 1:
         //Rectangle
         GUI->LoadFromBMP("rectangle.png", renderer);
         break;
      case 2:
         //Circle
         GUI->LoadFromBMP("circle.png", renderer);
         break;
      case 3:
         //Curved Line
         GUI->LoadFromBMP("curved.png", renderer);
         break;
      }
      SDL_Event incomingEvent;
      while (SDL_PollEvent(&incomingEvent))  //Checking which event is coming in
      {
         switch (incomingEvent.type)   //Using the type for a case statement
         {
         case SDL_QUIT:
            go = false;
            break;
         case SDL_MOUSEBUTTONDOWN:  //When the user presses the mouse button is will create a new object and add it to a vector
            switch (selector)
            {
            case 0:
               //Straight Line
               shapes.push_back(new StraightLine());   //Adding to vector
               shapes.back()->Point(incomingEvent, renderer);   //Calling the point function to start plotting the first point
               break;
            case 1:
               //Rectangle
               shapes.push_back(new Rectangle());    //etc. etc.
               shapes.back()->Point(incomingEvent, renderer);
               break;
            case 2:
               //Circle
               shapes.push_back(new Circle());
               shapes.back()->Point(incomingEvent, renderer);
               break;
            case 3:
               //Curved Line
               std::cout << "point1";
               shapes.push_back(new CurvedLine());
               shapes.back()->Point(incomingEvent, renderer, 0);
               break;
            case 5:
               //Fill
               SDL_Surface *surface = SDL_GetWindowSurface(window);
               Vec2 point = Bucket->Point(incomingEvent, renderer);
               std::cout<<Bucket->getpixel(surface, point.x, point.y);
               break;
            }
            break;
         case SDL_MOUSEBUTTONUP:
            switch (selector)
            {
            case 0:
            case 1:
            case 2:
               //Straight Line
               shapes.back()->Point(incomingEvent, renderer);   //I then access the same object created before and call Point again for the second point...
               break;
            case 3:
               //Curved Line
               shapes.back()->Point(incomingEvent, renderer, 1);
               selector = 4;
               break;
            case 4:
               //Control Point of Curved Line
               std::cout << "point3";
               shapes.back()->Point(incomingEvent, renderer, 2);   // Or sometimes the 3rd point based on the shape
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
     	for (int i = 0; i < shapes.size(); ++i)
     	{
     		shapes[i]->Draw(renderer);
     	}
     }

      //Drawing the GUI

      GUI->Draw(0, 0, renderer); 
      SDL_Rect temp = { 100, 100, 200, 50 };
      SDL_SetTextInputRect(&temp);

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

   //MESSY save stuff down here, all temporary
   //-----------------------------------------------------------------//
   //-----------------------------------------------------------------//
   if ((err = fopen_s(&f, "savedata.txt", "w")) != 0)
   {
      return 0;
   }
   else
   {
      if (!shapes.empty())
      {
         for (int i = 0; i < shapes.size(); ++i)
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

   //-----------------------------------------------------------------//
   //-----------------------------------------------------------------//

   // Our cleanup phase, hopefully fairly self-explanatory ;)
   SDL_DestroyWindow(window);
   SDL_Quit();

   return 0;
}
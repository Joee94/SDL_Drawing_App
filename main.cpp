
// This is the main SDL include file
#include <SDL.h>
// iostream is so we can output error messages to console
#include <iostream>
#include <vector>
#include "StraightLine.h"
#include "Rectangle.h"
#include "Circle.h"
#include "CurvedLine.h"


int main(int argc, char *argv[])
{
	// This is our initialisation phase

	// SDL_Init is the main initialisation function for SDL
	// It takes a 'flag' parameter which we use to tell SDL what systems we're going to use
	// Here, we want to use SDL's video system, so we give it the flag for this
	// Incidentally, this also initialises the input event system
	// This function also returns an error value if something goes wrong
	// So we can put this straight in an 'if' statement to check and exit if need be
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// Something went very wrong in initialisation, all we can do is exit
		std::cout << "Whoops! Something went very wrong, cannot initialise SDL :(" << std::endl;
		return -1;
	}



	// Now we have got SDL initialised, we are ready to create a window!
	// These are some variables to help show you what the parameters are for this function
	// You can experiment with the numbers to see what they do
	int winPosX = 100;
	int winPosY = 100;
	int winWidth = 640;
	int winHeight = 480;
	SDL_Window *window = SDL_CreateWindow("My Window!!!",  // The first parameter is the window title
		winPosX, winPosY,
		winWidth, winHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	// The last parameter lets us specify a number of options
	// Here, we tell SDL that we want the window to be shown and that it can be resized
	// You can learn more about SDL_CreateWindow here: https://wiki.libsdl.org/SDL_CreateWindow?highlight=%28\bCategoryVideo\b%29|%28CategoryEnum%29|%28CategoryStruct%29
	// The flags you can pass in for the last parameter are listed here: https://wiki.libsdl.org/SDL_WindowFlags

	// The SDL_CreateWindow function returns an SDL_Window
	// This is a structure which contains all the data about our window (size, playerPosition, etc)
	// We will also need this when we want to draw things to the window
	// This is therefore quite important we don't lose it!


	// The SDL_Renderer is a structure that handles rendering
	// It will store all of SDL's internal rendering related settings
	// When we create it we tell it which SDL_Window we want it to render to
	// That renderer can only be used for this window
	// (yes, we can have multiple windows - feel free to have a play sometime)
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);


	// Create a sprite

	//-----------------

	// We are going to work out how much time passes from frame to frame
	// We will use this variable to store the time at our previous frame
	// This function returns the number of milliseconds since SDL was initialised
	unsigned int lastTime = SDL_GetTicks();


	// Ok, hopefully finished with initialisation now
	// Let's go and draw something!

	// We will use these variables to store the playerPosition of our sprite


	// We will use these to store 'commands' which result from our key inputs
	// I am assuming here that we are making a top-down vertical scrolling game,
	// So 'forwards' is a command to move up the screen
	// 'backwards' is a command to move down the screen
	// In reality this may be similar to keeping track of, say the arrow keys, but
	// conceptually it provides us with an abstraction - we might want to map it to other keys!
	// This way we only need to change our input event code so that other keys modify the commands
	bool cmd_forwards, cmd_backwards, cmd_left, cmd_right;
	cmd_forwards = cmd_backwards = cmd_left = cmd_right = false;

	// We are now preparing for our main loop (also known as the 'game loop')
	// This loop will keep going round until we exit from our program by changing the bool 'go' to the value false
	// This loop is an important concept and forms the basis of most games you'll be writing
	// Within this loop we generally do the following things:
	//   * Check for input from the user (and do something about it!)
	//   * Update our world
	//   * Draw our world
	// We will come back to this in later lectures


	bool go = true;

	std::vector<Shape*> shapes;

	std::vector<StraightLine*> lines;
	std::vector<Rectangle*> rectangles;
	std::vector<Circle*> circles;
	std::vector<CurvedLine*> curvedlines;

	int selector = 3;
	int test = 0;

	while (go)
	{
		SDL_Event incomingEvent;
		// SDL_PollEvent will check if there is an event in the queue
		// If there's nothing in the queue it won't sit and wait around for an event to come along (there are functions which do this, and that can be useful too!)
		// For an empty queue it will simply return 'false'
		// If there is an event, the function will return 'true' and it will fill the 'incomingEvent' we have given it as a parameter with the event data
		while (SDL_PollEvent(&incomingEvent))
		{
			// If we get in here, we have an event and need to figure out what to do with it
			// For now, we will just use a switch based on the event's type
			switch (incomingEvent.type)
			{
			case SDL_QUIT:
				// The event type is SDL_QUIT
				// This means we have been asked to quit - probably the user clicked on the 'x' at the top right corner of the window
				// To quit we need to set our 'go' bool to false so that we can escape out of the game loop
				go = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (selector)
				{
				case 0:
					shapes.push_back(new Shape());
					lines.push_back(new StraightLine());
					lines.back()->Point(incomingEvent, renderer);
					break;
				case 1:
					shapes.push_back(new Shape());
					rectangles.push_back(new Rectangle());
					rectangles.back()->Point(incomingEvent, renderer);
					break;
				case 2:
					shapes.push_back(new Shape());
					circles.push_back(new Circle());
					circles.back()->Point(incomingEvent, renderer);
					break;
				case 3:
					shapes.push_back(new Shape());
					std::cout << "point1";
					curvedlines.push_back(new CurvedLine());
					curvedlines.back()->Point(incomingEvent, renderer, 0);
					break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				switch (selector)
				{
				case 0:
					lines.back()->Point(incomingEvent, renderer);
					break;
				case 1:
					rectangles.back()->Point(incomingEvent, renderer);
					break;
				case 2:
					circles.back()->Point(incomingEvent, renderer);
					break;
				case 3:
					curvedlines.back()->Point(incomingEvent, renderer, 1);
					selector = 4;
					break;
				case 4:
					std::cout << "point3";
					curvedlines.back()->Point(incomingEvent, renderer, 2);
					selector = 3;
					break;

				}
				break;
			case SDL_KEYDOWN:
				switch (incomingEvent.key.keysym.sym)
			{

				case SDLK_1:
					selector = 0;
					std::cout << "0";
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
			}
				 break;
				// If you want to learn more about event handling and different SDL event types, see:
				// https://wiki.libsdl.org/SDL_Event
				// and also: https://wiki.libsdl.org/SDL_EventType
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

		// Draw our sprite at the given playerPosition!
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

		if (!lines.empty())
		{
			for (int i = 0; i < lines.size(); ++i)
			{
				lines[i]->Draw(renderer);
			}
		}
		
		if (!rectangles.empty())
		{
			for (int i = 0; i < rectangles.size(); ++i)
			{
				rectangles[i]->Draw(renderer);
			}
		}
		
		if (!circles.empty())
		{
			for (int i = 0; i < circles.size(); ++i)
			{
				circles[i]->Draw(renderer);
			}
		}
		
		if (!curvedlines.empty())
		{
			for (int i = 0; i < curvedlines.size(); ++i)
			{
				curvedlines[i]->Draw(renderer);
			}
		}

		if (!shapes.empty())
		{
			for (int i = 0; i < shapes.size(); ++i)
			{
				shapes[i]->Draw(renderer);
			}
		}


		// This tells the renderer to actually show its contents to the screen
		// We'll get into this sort of thing at a later date - or just look up 'double buffering' if you're impatient :P
		SDL_RenderPresent(renderer);


		// Limiter in case we're running really quick
		if (deltaTs < (1.0f / 50.0f))	// not sure how accurate the SDL_Delay function is..
		{
			SDL_Delay((unsigned int)(((1.0f / 50.0f) - deltaTs)*1000.0f));
		}

		//std::cout << lines.size();
	}
	// If we get outside the main game loop, it means our user has requested we exit



	// Our cleanup phase, hopefully fairly self-explanatory ;)
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

void DrawShapes(int test)
{

}
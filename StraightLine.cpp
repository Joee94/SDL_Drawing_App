#include "StraightLine.h"

StraightLine::StraightLine()
{
   //Create some points...
   point1 = new Vec2();
   point2 = new Vec2();
   shapeType = 0;
}

StraightLine::~StraightLine()
{
   //...Destroy some points
   delete point1;
   delete point2;
}

void StraightLine::CreateArray(SDL_Event& mouseEvent)
{
   // Variable for storing our VAO
   VAO = 0;
   // OpenGL has its own defined datatypes - a 'GLuint' is basically an unsigned int
   // Creates one VAO
   glGenVertexArrays(1, &VAO);
   // 'Binding' something makes it the current one we are using
   // This is like activating it, so that subsequent function calls will work on this item
   glBindVertexArray(VAO);

   static const GLfloat g_vertex_buffer_data[] =
   {
      point1->x, point1->y, 0.0f,
      point2->x, point2->y, 0.0f,
   };

   // Variable for storing a VBO
   GLuint buffer = 0;
   // Create a generic 'buffer'
   glGenBuffers(1, &buffer);
   // Tell OpenGL that we want to activate the buffer and that it's a VBO
   glBindBuffer(GL_ARRAY_BUFFER, buffer);
   // With this buffer active, we can now send our data to OpenGL
   // We need to tell it how much data to send
   // We can also tell OpenGL how we intend to use this buffer - here we say GL_STATIC_DRAW because we're only writing it once
   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, g_vertex_buffer_data, GL_STATIC_DRAW);

   // This tells OpenGL how we link the vertex data to the shader
   // (We will look at this properly in the lectures)
   glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
   glEnableVertexAttribArray(0);

   // Unbind for neatness, it just makes life easier
   // As a general tip, especially as you're still learning, for each function that needs to do something specific try to return OpenGL in the state you found it in
   // This means you will need to set the states at the beginning of your function and set them back at the end
   // If you don't do this, your function could rely on states being set elsewhere and it's easy to lose track of this as your project grows
   // If you then change the code from elsewhere, your current code could mysteriously stop working properly!
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);


}

void StraightLine::glDraw()
{
   // Ok, here I like to indent drawing calls - it's just a personal style, you may not like it and that's fine ;)
   // Generally you will need to be activating and deactivating OpenGL states
   // I just find it visually easier if the activations / deactivations happen at different tab depths
   // This can help when things get more complex

   // Activate the shader program

   // Activate the VAO
   glBindVertexArray(VAO);
   // Tell OpenGL to draw it
   // Must specify the type of geometry to draw and the number of vertices
   glDrawArrays(GL_TRIANGLES, 0, 2);

   // Unbind VAO
   glBindVertexArray(0);

   // Technically we can do this, but it makes no real sense because we must always have a valid shader program to draw geometry
   glUseProgram(0);
}


void StraightLine::Draw(SDL_Renderer* renderer, float r, float g, float b, float a)
{
   //This is an easy one, set a colour and draw it, thanks to inheritance I don't have to worry about the mouseinput stuff
   SDL_SetRenderDrawColor(renderer, r, g, b, a);
   SDL_RenderDrawLine(renderer, point1->x, point1->y, point2->x, point2->y);
}

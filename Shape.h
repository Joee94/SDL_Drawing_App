#pragma once
#include <SDL.h>
#include <vector>
#include <iostream>
#include "Vec2.h"
#define PI 3.14159265359f

/// The base class for all the shapes

class Shape
{
public:
   /// \brief Lets you plot a point for the basic shapes
	/// \param mouseEvent takes in what your mouse is doing
   virtual void Point(SDL_Event& mouseEvent);   //Virtual so I can overwrite them when I need to

   /// \brief Lets you plot a point for more complex shapes
   /// \param mouseEvent takes in what your mouse is doing
   /// \param num the nth time you need to access a certain mouse event
   virtual void Point(SDL_Event& mouseEvent, int num);

   /// \brief Lets you plot a point when you know all the parameters, 2 points
   /// \param p1x point1 x co-ordinate
   /// \param p1y point1 y co-ordinate
   /// \param p2x point2 x co-ordinate
   /// \param p2y point2 y co-ordinate
   virtual void Point(float p1x, float p1y, float p2x, float p2y);

   /// \brief Lets you plot a point when you know all the parameters, 3 points
   /// \param p1x point1 x co-ordinate
   /// \param p1y point1 y co-ordinate
   /// \param p2x point2 x co-ordinate
   /// \param p2y point2 y co-ordinate
   /// \param p3x point3 x co-ordinate
   /// \param p3y point3 y co-ordinate
   virtual void Point(float p1x, float p1y, float p2x, float p2y, float p3x, float p3y);

   /// \brief Lets you plot a point when you know all the parameters, 3 points
   /// \param p1x point1 x co-ordinate
   /// \param p1y point1 y co-ordinate
   /// \param p2x point2 x co-ordinate
   /// \param p2y point2 y co-ordinate
   /// \param p3x point3 x co-ordinate
   /// \param p3y point3 y co-ordinate
   /// \param p4x point4 x co-ordinate
   /// \param p4y point4 y co-ordinate
   virtual void Point(float p1x, float p1y, float p2x, float p2y, float p3x, float p3y, float p4x, float p4y);

   /// \brief Draws your shape
   /// \param renderer the renderer to draw to
   /// \param r red
   /// \param g green
   /// \param b blue
   /// \param a alpha
   virtual void Draw(SDL_Renderer* renderer, float r, float g, float b, float a);

   /// \brief Sets the colour of your shapes
   /// \param red red
   /// \param green green
   /// \param blue blue
   /// \param alpha alpha
   virtual void Colour(uint8_t &red, uint8_t &green, uint8_t &blue, uint8_t &alpha);

   /// \brief Returns Point1
   Vec2 GetPoint1();
   /// \brief Returns Point2
   Vec2 GetPoint2();
   /// \brief Returns ControlPoint
   Vec2 GetControlPoint();
   /// \brief Returns ControlPoint1
   Vec2 GetControlPoint2();
   /// \brief Returns ShapeType
   uint8_t GetShapeType();
   /// \brief Returns Red
   uint8_t GetR();
   /// \brief Returns Green
   uint8_t GetG();
   /// \brief Returns Blue
   uint8_t GetB();
   /// \brief Returns Alpha
   uint8_t GetA();
   /// \brief Returns Points Array
   std::vector<Vec2> getPoints();

protected:
   Vec2* point1;        ///<The first point
   Vec2* point2;        ///<The second point
   Vec2* controlPoint;  ///<The first control point
   Vec2* controlPoint2; ///<The second control point

   uint8_t r;  ///< Red
   uint8_t g;  ///< Green
   uint8_t b;  ///< Blue
   uint8_t a;  ///< Alpha

   uint8_t shapeType;   //<The shape type
   std::vector<Vec2> points;  //<Number of points in a fill
};
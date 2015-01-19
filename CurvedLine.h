#pragma once
#include "Shape.h"

/// The Quadratic curve class
class CurvedLine : public Shape
{
public:
   /// \brief Quadratic Curved line constructor
   CurvedLine();
   /// \brief Quadratic Curved line destructor
   ~CurvedLine();

   void Draw(SDL_Renderer* renderer, float r, float g, float b, float a);

   /// \brief Finds where the point should be drawn in relation to the control points
   /// \param a The Starting Point
   /// \param b The End Point
   /// \param control The first Control point
   /// \param t the number of points
   Vec2 QuadBezierSample(Vec2 a, Vec2 b, Vec2 control, float t);

   /// \brief Returns the control point
   Vec2 GetControlPoint();

private:
   /// \brief the number of points
   int numSamples = 100;
};
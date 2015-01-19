#pragma once
#include "Shape.h"

/// The Cubic Curve class
class CurvedLine2 : public Shape
{
public:
   /// \brief Cubic Curved line constructor
   CurvedLine2();
   /// \brief Cubic Curved line destructor
   ~CurvedLine2();

   void Draw(SDL_Renderer* renderer, float r, float g, float b, float a);

   /// \brief Finds where the point should be drawn in relation to the control points
   /// \param a The Starting Point
   /// \param b The End Point
   /// \param control The first Control point
   /// \param control2 The second Control point
   /// \param t the number of points
   Vec2 CubicBezierSample(Vec2 a, Vec2 b, Vec2 control, Vec2 control2, float t);

   /// \brief Returns the control point
   Vec2 GetControlPoint();

   /// \brief Returns the second control point
   Vec2 GetControlPoint2();

private:
   /// \brief the number of points
   int numSamples = 100;
};
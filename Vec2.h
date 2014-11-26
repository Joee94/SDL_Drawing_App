#pragma once
#include <cmath>

/// declares a type called 'Vec2' that represents a 2D vector
struct Vec2 
{
  float x; ///< the X coordinate 
  float y; ///< the Y coordinate

  // constructor functions (specifies what happens when you create a new Vec2)
  Vec2() : x(0), y(0) {}
  Vec2(float s) : x(s), y(s) {}
  Vec2(float X, float Y) : x(X), y(Y) {}

  // more stuff to ignore! (Specify what happens when using +=, -=, etc)
  const Vec2& operator  = (Vec2 b);
  const Vec2& operator += (Vec2 b);
  const Vec2& operator -= (Vec2 b);
  const Vec2& operator *= (float b);
  const Vec2& operator /= (float b);
}; 

/// performs the dot product between two vectors
inline float dot(Vec2 a, Vec2 b)
{
  return (a.x * b.x) + (a.y * b.y);
}

/// returns the squared length of the vector a
inline float length2(Vec2 a)
{
  return dot(a, a);
}

/// returns the length of vector a
inline float length(Vec2 a)
{
  return std::sqrt(length2(a));
}

/// normalises the 2D vector so it is unit length
inline Vec2 normalize(Vec2 a)
{
  float l = length(a);
  // handle division by zero :(
  if(std::fabs(l) > 1e-5f)
  {
    l = 1.0f / l;
  }
  else
  {
    l = 0.0f;
  }
  return Vec2(l * a.x, l * a.y);
}

/// unary negation
inline Vec2 operator - (Vec2 a)
{
  Vec2 r;
  r.x = -a.x;
  r.y = -a.y;
  return r;
}

/// adds two Vec2's. 
inline Vec2 operator + (Vec2 a, Vec2 b)
{
  Vec2 r;
  r.x = a.x + b.x;
  r.y = a.y + b.y;
  return r;
}

/// subtracts two Vec2's. 
inline Vec2 operator - (Vec2 a, Vec2 b)
{
  Vec2 r;
  r.x = a.x - b.x;
  r.y = a.y - b.y;
  return r;
}

/// multiplies a float by a Vec2
inline Vec2 operator * (float b, Vec2 a)
{
  Vec2 r;
  r.x = a.x * b;
  r.y = a.y * b;
  return r;
}

/// multiplies a Vec2 by a float
inline Vec2 operator * (Vec2 a, float b)
{
  Vec2 r;
  r.x = a.x * b;
  r.y = a.y * b;
  return r;
}

/// divides a Vec2 by a float
inline Vec2 operator / (Vec2 a, float b)
{
  Vec2 r;
  r.x = a.x / b;
  r.y = a.y / b;
  return r;
}

/// specifies the = operator for Vec2
inline const Vec2& Vec2::operator = (Vec2 b)
{
  x = b.x;
  y = b.y;
  return *this;
}

/// specifies the += operator for Vec2
inline const Vec2& Vec2::operator += (Vec2 b)
{
  x += b.x;
  y += b.y;
  return *this;
}

/// specifies the -= operator for Vec2
inline const Vec2& Vec2::operator -= (Vec2 b)
{
  x -= b.x;
  y -= b.y;
  return *this;
}

/// specifies the *= operator for Vec2
inline const Vec2& Vec2::operator *= (float b)
{
  x *= b;
  y *= b;
  return *this;
}

/// specifies the /= operator for Vec2
inline const Vec2& Vec2::operator /= (float b)
{
  x /= b;
  y /= b;
  return *this;
}


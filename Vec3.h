#pragma once
#include "Vec2.h"

/// declares a type called 'Vec3' that represents a 3D vector
struct Vec3 
{
  float x; ///< the X coordinate 
  float y; ///< the Y coordinate
  float z; ///< the Y coordinate

  // constructor functions (specifies what happens when you create a new Vec3)
  Vec3() : x(0), y(0), z(0) {}
  Vec3(float s) : x(s), y(s), z(s) {}
  Vec3(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
  Vec3(Vec2 xy, float Z = 0) : x(xy.x), y(xy.y), z(Z) {}

  // more stuff to ignore! (Specify what happens when using +=, -=, etc)
  const Vec3& operator  = (const Vec3& b);
  const Vec3& operator += (const Vec3& b);
  const Vec3& operator -= (const Vec3& b);
  const Vec3& operator *= (float b);
  const Vec3& operator /= (float b);

  /// cast to Vec2
  operator Vec2 () const
    { return Vec2(x, y); }
}; 

/// performs the dot product between two vectors
inline float dot(const Vec3& a, const Vec3& b)
{
  return (a.x * b.x) + (a.y * b.y)  + (a.z * b.z);
}

/// returns the squared length of the vector a
inline float length2(const Vec3& a)
{
  return dot(a, a);
}

/// returns the length of vector a
inline float length(const Vec3& a)
{
  return std::sqrt(length2(a));
}

/// normalises the 3D vector so it is unit length
inline Vec3 normalize(const Vec3& a)
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
  return Vec3(l * a.x, l * a.y, l * a.z);
}

/// unary negation
inline Vec3 operator - (const Vec3& a)
{
  Vec3 r;
  r.x = -a.x;
  r.y = -a.y;
  r.z = -a.z;
  return r;
}

/// adds two Vec3's. 
inline Vec3 operator + (const Vec3& a, const Vec3& b)
{
  Vec3 r;
  r.x = a.x + b.x;
  r.y = a.y + b.y;
  r.z = a.z + b.z;
  return r;
}

/// subtracts two Vec3's. 
inline Vec3 operator - (const Vec3& a, const Vec3& b)
{
  Vec3 r;
  r.x = a.x - b.x;
  r.y = a.y - b.y;
  r.z = a.z - b.z;
  return r;
}

/// multiplies a float by a Vec3
inline Vec3 operator * (float b, const Vec3& a)
{
  Vec3 r;
  r.x = a.x * b;
  r.y = a.y * b;
  r.z = a.z * b;
  return r;
}

/// multiplies a Vec3 by a float
inline Vec3 operator * (const Vec3& a, float b)
{
  Vec3 r;
  r.x = a.x * b;
  r.y = a.y * b;
  r.z = a.z * b;
  return r;
}

/// divides a Vec3 by a float
inline Vec3 operator / (const Vec3& a, float b)
{
  Vec3 r;
  r.x = a.x / b;
  r.y = a.y / b;
  r.z = a.z / b;
  return r;
}

/// specifies the = operator for Vec3
inline const Vec3& Vec3::operator = (const Vec3& b)
{
  x = b.x;
  y = b.y;
  z = b.z;
  return *this;
}

/// specifies the += operator for Vec3
inline const Vec3& Vec3::operator += (const Vec3& b)
{
  x += b.x;
  y += b.y;
  z += b.z;
  return *this;
}

/// specifies the -= operator for Vec3
inline const Vec3& Vec3::operator -= (const Vec3& b)
{
  x -= b.x;
  y -= b.y;
  z -= b.z;
  return *this;
}

/// specifies the *= operator for Vec3
inline const Vec3& Vec3::operator *= (float b)
{
  x *= b;
  y *= b;
  z *= b;
  return *this;
}

/// specifies the /= operator for Vec3
inline const Vec3& Vec3::operator /= (float b)
{
  x /= b;
  y /= b;
  z /= b;
  return *this;
}


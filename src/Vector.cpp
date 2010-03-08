#include "Vector.hpp"
#include "m3gexcept.hpp"
#include <iostream>
#include <cmath>
using namespace std;
using namespace m3g;


Vector:: Vector () : x(0), y(0), z(0), w(1)
{
}

Vector:: Vector (float x_, float y_, float z_, float w_) :
  x(x_), y(y_), z(z_), w(w_)
{
}

Vector:: ~Vector ()
{
}

void Vector:: get (float* xyz) const
{
  if (w == 0) {
    throw null_point_error ("W component is 0.");
  }
  xyz[0] = x/w; 
  xyz[1] = y/w;
  xyz[2] = z/w;
}

float& Vector:: operator[] (int n)
{
  if (n < 0 || n > 3) {
    throw invalid_argument ("Index of Vector is out of range.");
  }
  return (&x)[n];
}

const float& Vector:: operator[] (int n) const
{
  if (n < 0 || n > 3) {
    throw invalid_argument ("Index of Vector is out of range.");
  }
  return (&x)[n];
}

void Vector:: normalize ()
{
  float len = sqrtf(x*x+y*y+z*z);
  if (len == 0) {
    throw null_point_error ("Divided by 0.");
  }
  x /= len;
  y /= len;
  z /= len;
}

float m3g::dot (const Vector& p, const Vector& q)
{
  return sqrtf (p.x*q.x+p.y*q.y+p.z*q.z);
}

Vector m3g::cross (const Vector& p, const Vector& q)
{
  return Vector (p.y*q.z-p.z*q.y, p.z*q.x-p.x*q.z, p.x*q.y-p.y*q.x);
}

Vector operator+ (const Vector& lhs, const Vector& rhs)
{
  if (lhs.w != rhs.w && lhs.w != 0 && rhs.w != 0) {
    throw invalid_argument ("Plus of Invalid w component of Vector is invalid.");
  }

  if (lhs.w == rhs.w) {
    return Vector(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w);
  } else {
    return Vector(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
  }
}

std::ostream& operator<< (std::ostream& out , const m3g::Vector& v)
{
  return out << v.x << ", " << v.y << ", " << v.z << ", " << v.w;
}


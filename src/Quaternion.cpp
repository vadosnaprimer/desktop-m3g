#include "Quaternion.hpp"
#include "Exception.hpp"
#include "m3ginternal.hpp"
#include <iostream>
#include <cmath>
using namespace std;
using namespace m3g;

Quaternion:: Quaternion () :
  x(0), y(0), z(0), w(1)
{
}

Quaternion:: Quaternion (float angle, float ax, float ay, float az) :
  x(0), y(0), z(0), w(1)
{
  if (fabs((ax*ax+ay*ay+az*az)-1) > M3G_EPSILON) {
    //cout << (ax*ax+ay*ay+az*az-1) << " <--> " << M3G_EPSILON << "\n";
    //cout << ax << ", " << ay << ", " << az << "\n";
    throw IllegalArgumentException (__FILE__, __func__, "Length of rotation axis must be 1 for Quaternion.");
  }

  float th = 2*M_PI*angle/360.f;
  x = ax * sinf (th/2.f);
  y = ay * sinf (th/2.f);
  z = az * sinf (th/2.f);
  w =      cosf (th/2.f);
}

Quaternion:: ~Quaternion ()
{
}

void Quaternion:: set (float qx, float qy, float qz, float qw)
{
  x = qx;
  y = qy;
  z = qz;
  w = qw;
}

/**
 * (補足) 回転角度が0の場合はangle=0,axis=(x,y,z)が返る.
 */
void Quaternion:: getAngleAxis (float* angle_axis) const
{
  if (angle_axis == NULL) {
    throw NullPointException (__FILE__, __func__, "Angle_axis is NULL.");
  }

  float th = 2*acosf(w);
  angle_axis[0] = th*360/(2.f*M_PI);
  if (sinf(th/2.f) != 0) {
    angle_axis[1] = x/sinf(th/2.f);
    angle_axis[2] = y/sinf(th/2.f);
    angle_axis[3] = z/sinf(th/2.f);
  } else {
    angle_axis[1] = x;
    angle_axis[2] = y;
    angle_axis[3] = z;
  }
}


Quaternion m3g::slerp (const Quaternion& p, const Quaternion& q, float a)
  {
    float th = acosf(p.x*q.x + p.y*q.y + p.z*q.z + p.w*q.w);
    float w0 = sinf((1-a)*th)/sinf(th);
    float w1 = sinf(a*th)/sinf(th);
    return w0*p + w1*q;
  }

Quaternion operator* (float f, const Quaternion& p)
  {
    Quaternion r;
    r.x = f*p.x;
    r.y = f*p.y;
    r.z = f*p.z;
    r.w = f*p.w;
    return r;
  }

  Quaternion operator* (const Quaternion& p, float f)
  {
    return f*p;
  }

/**
 * クォータニオンpを適応してからクォータニオンqを適応する.
 */
  Quaternion operator* (const Quaternion& p, const Quaternion& q)
  {
    Quaternion r;
    r.x = p.w*q.x + q.w*p.x + p.y*q.z - p.z*q.y;
    r.y = p.w*q.y + q.w*p.y + p.z*q.x - p.x*q.z;
    r.z = p.w*q.z + q.w*p.z + p.x*q.y - p.y*q.x;
    r.w = p.w*q.w - p.x*q.x - p.y*q.y - p.z*q.z;
    return r;
  }

  Quaternion operator+ (const Quaternion& p, const Quaternion& q)
  {
    Quaternion r;
    r.x = p.x + q.x;
    r.y = p.y + q.y;
    r.z = p.z + q.z;
    r.w = p.w + q.w;
    return r;
  }

std::ostream& operator<< (std::ostream& out, const Quaternion& q)
{
  out << "(" << q.x << "," << q.y << "," << q.z << "," << q.w << ") or ";
  float a[4];
  q.getAngleAxis (a);
  out << "(" << a[0] << " ," << a[1] << "," << a[2] << "," << a[3] << ")";
  return out;
}

#include <unittest++/UnitTest++.h>
#include <iostream>
#include "Vector.hpp"
using namespace std;
using namespace m3g;

TEST (Vector_set_variables)
{
  Vector v (1,2,3,4);
  
  CHECK_EQUAL (1.f, v[0]);
  CHECK_EQUAL (2.f, v[1]);
  CHECK_EQUAL (3.f, v[2]);
  CHECK_EQUAL (4.f, v[3]);
  
  float f[4] = {0,0,0,999};

  v.get (f);
  CHECK_EQUAL (1/4.f, f[0]);
  CHECK_EQUAL (2/4.f, f[1]);
  CHECK_EQUAL (3/4.f, f[2]);
  CHECK_EQUAL (999.f, f[3]);
}

TEST (Vector_normal)
{
  Vector v0 (2,0,0);
  Vector v1 (0,2,0);
  Vector v2 (0,0,2);
  v0.normalize();
  v1.normalize();
  v2.normalize();
  CHECK_CLOSE (1, v0.x, 0.00001);
  CHECK_CLOSE (1, v1.y, 0.00001);
  CHECK_CLOSE (1, v2.z, 0.00001);
}

TEST (Vector_dot_cross)
{
  Vector v0 (1,0,0);
  Vector v1 (0,1,0);
  Vector v2 (0,0,1);

  CHECK_CLOSE (0, dot(v0,v1), 0.00001);
  CHECK_CLOSE (0, dot(v1,v2), 0.00001);
  CHECK_CLOSE (0, dot(v2,v0), 0.00001);
  CHECK_CLOSE (1, dot(v0,v0), 0.00001);
  CHECK_CLOSE (1, dot(v1,v1), 0.00001);
  CHECK_CLOSE (1, dot(v2,v2), 0.00001);

  CHECK_CLOSE (0, cross(v0,v1).x, 0.00001);
  CHECK_CLOSE (0, cross(v0,v1).y, 0.00001);
  CHECK_CLOSE (1, cross(v0,v1).z, 0.00001);
  CHECK_CLOSE (1, cross(v1,v2).x, 0.00001);
  CHECK_CLOSE (0, cross(v1,v2).y, 0.00001);
  CHECK_CLOSE (0, cross(v1,v2).z, 0.00001);
  CHECK_CLOSE (0, cross(v2,v0).x, 0.00001);
  CHECK_CLOSE (1, cross(v2,v0).y, 0.00001);
  CHECK_CLOSE (0, cross(v2,v0).z, 0.00001);
}

TEST (Vector_plus)
{
  Vector v0(1,2,3,2);
  Vector v1(2,4,6,2);
  Vector v3;

  v3 = v0 + v1;

  CHECK_CLOSE (3, v3.x, 0.00001);
  CHECK_CLOSE (6, v3.y, 0.00001);
  CHECK_CLOSE (9, v3.z, 0.00001);
  CHECK_CLOSE (2, v3.w, 0.00001);
}


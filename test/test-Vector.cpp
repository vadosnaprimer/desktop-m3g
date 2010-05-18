#include <unittest++/UnitTest++.h>
#include <iostream>
#include <cmath>
#include "Vector.hpp"
using namespace std;
using namespace m3g;


TEST (Vector_defualt_variables)
{
    Vector v;

    CHECK_EQUAL (0, v[0]);
    CHECK_EQUAL (0, v[1]);
    CHECK_EQUAL (0, v[2]);
    CHECK_EQUAL (1, v[3]);
}

TEST (Vector_set_variables)
{
    Vector v0 (1,2,3,4);
  
    CHECK_EQUAL (1.f, v0[0]);
    CHECK_EQUAL (2.f, v0[1]);
    CHECK_EQUAL (3.f, v0[2]);
    CHECK_EQUAL (4.f, v0[3]);

    float f[4] = {5,6,7};
    Vector v1 (f);

    CHECK_EQUAL (5.f, v1[0]);
    CHECK_EQUAL (6.f, v1[1]);
    CHECK_EQUAL (7.f, v1[2]);
    CHECK_EQUAL (1.f, v1[3]);

    float value[4] = {0,0,0,0};

    v0.get (value);
    CHECK_EQUAL (1/4.f, value[0]);
    CHECK_EQUAL (2/4.f, value[1]);
    CHECK_EQUAL (3/4.f, value[2]);
    CHECK_EQUAL (0.f  , value[3]);

    v1.get (value);
    CHECK_EQUAL (5.f, value[0]);
    CHECK_EQUAL (6.f, value[1]);
    CHECK_EQUAL (7.f, value[2]);
    CHECK_EQUAL (0.f, value[3]);
}

TEST (Vector_length)
{
    Vector v (1,2,3,4);
    float len = sqrtf((float)(1*1+2*2+3*3)/(4*4));
    CHECK_EQUAL (len, v.length());
}

TEST (Vector_normalize)
{
    Vector v0 (2,1,0);
    Vector v1 (0,2,0,2);
    Vector v2 (0,-1,2,1);
    v0.normalize();
    v1.normalize();
    v2.normalize();
    CHECK_CLOSE (1, v0.length(), 0.00001);
    CHECK_CLOSE (1, v1.length(), 0.00001);
    CHECK_CLOSE (1, v2.length(), 0.00001);

    //cout << "v0 = " << v0 << "\n";
    //cout << "v1 = " << v1 << "\n";
    //cout << "v2 = " << v2 << "\n";
}

TEST (Vector_divided_by_w)
{
    Vector v0 (4,6,8,2);
    v0.divided_by_w ();
    CHECK_CLOSE (2, v0.x, 0.00001f);
    CHECK_CLOSE (3, v0.y, 0.00001f);
    CHECK_CLOSE (4, v0.z, 0.00001f);
    CHECK_CLOSE (1, v0.w, 0.00001f);

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

TEST (Vector_minu)
{
    Vector v0(1,2,3,2);
    Vector v1(2,4,6,2);
    Vector v3;

    v3 = v1 - v0;

    CHECK_CLOSE (1, v3.x, 0.00001);
    CHECK_CLOSE (2, v3.y, 0.00001);
    CHECK_CLOSE (3, v3.z, 0.00001);
    CHECK_CLOSE (2, v3.w, 0.00001);
}

TEST (Vector_unary_minus)
{
    Vector v0(1,2,3,2);
    Vector v1 = -v0;
    CHECK_CLOSE (-1, v1.x, 0.00001);
    CHECK_CLOSE (-2, v1.y, 0.00001);
    CHECK_CLOSE (-3, v1.z, 0.00001);
    CHECK_CLOSE (2,  v1.w, 0.00001);
}

TEST (Vector_plus_equal)
{
    Vector v0(1,2,3,2);
    Vector v1(2,4,6,2);
    Vector v2(-1,-2,-3,1);
    Vector v3(0,2,4,2);

    v0 += v1;

    CHECK_CLOSE (3, v0.x, 0.00001);
    CHECK_CLOSE (6, v0.y, 0.00001);
    CHECK_CLOSE (9, v0.z, 0.00001);
    CHECK_CLOSE (2, v0.w, 0.00001);

    v2 += v3;

    CHECK_CLOSE (-1, v2.x, 0.00001);
    CHECK_CLOSE (-1, v2.y, 0.00001);
    CHECK_CLOSE (-1, v2.z, 0.00001);
    CHECK_CLOSE ( 1, v2.w, 0.00001);

}

TEST (Vector_mul_float)
{
    Vector v0(1,2,3,2);
    Vector v1;
    Vector v3;

    v0 = v0 * 2;

    CHECK_CLOSE (2, v0.x, 0.00001);
    CHECK_CLOSE (4, v0.y, 0.00001);
    CHECK_CLOSE (6, v0.z, 0.00001);
    CHECK_CLOSE (2, v0.w, 0.00001);

    v0 = 3 * v0;

    CHECK_CLOSE (6, v0.x, 0.00001);
    CHECK_CLOSE (12, v0.y, 0.00001);
    CHECK_CLOSE (18, v0.z, 0.00001);
    CHECK_CLOSE (2, v0.w, 0.00001);
}

TEST (Vector_div_float)
{
    Vector v0(2,4,6,8);
    v0 = v0 / 2.f;

    CHECK_CLOSE (1, v0.x, 0.00001);
    CHECK_CLOSE (2, v0.y, 0.00001);
    CHECK_CLOSE (3, v0.z, 0.00001);
    CHECK_CLOSE (8, v0.w, 0.00001);

}


TEST (Vector_dot)
{
    Vector v1 = Vector(1,0,0).normalize();
    Vector v2 = Vector(1,1,0).normalize();
    Vector v3 = Vector(-1,1,0).normalize();
    Vector v4 = Vector(-1,0,0).normalize();

    CHECK_CLOSE (1,            dot(v1,v1), 0.00001f);
    CHECK_CLOSE (0.70710678f,  dot(v1,v2), 0.00001f);
    CHECK_CLOSE (-0.70710678f, dot(v1,v3), 0.00001f);
    CHECK_CLOSE (-1,           dot(v1,v4), 0.00001f);
}

TEST (Vector_cross)
{
    Vector v1 = Vector(1,0,0).normalize();
    Vector v2 = Vector(1,1,0).normalize();
    Vector v3 = Vector(-1,1,0).normalize();
    Vector v4 = Vector(-1,0,0).normalize();

    //cout << "v1 x v1 = " << cross(v1, v1) << "\n";
    //cout << "v1 x v2 = " << cross(v1, v2) << "\n";
    //cout << "v1 x v3 = " << cross(v1, v3) << "\n";
    //cout << "v1 x v4 = " << cross(v1, v4) << "\n";

    CHECK_CLOSE (0, cross(v1,v1).x, 0.00001f);
    CHECK_CLOSE (0, cross(v1,v1).y, 0.00001f);
    CHECK_CLOSE (0, cross(v1,v1).z, 0.00001f);
    CHECK_CLOSE (1, cross(v1,v1).w, 0.00001f);

    CHECK_CLOSE (0,        cross(v1,v2).x, 0.00001f);
    CHECK_CLOSE (0,        cross(v1,v2).y, 0.00001f);
    CHECK_CLOSE (0.707107, cross(v1,v2).z, 0.00001f);
    CHECK_CLOSE (1,        cross(v1,v2).w, 0.00001f);

    CHECK_CLOSE (0,        cross(v1,v3).x, 0.00001f);
    CHECK_CLOSE (0,        cross(v1,v3).y, 0.00001f);
    CHECK_CLOSE (0.707107, cross(v1,v3).z, 0.00001f);
    CHECK_CLOSE (1,        cross(v1,v3).w, 0.00001f);

    CHECK_CLOSE (0,        cross(v1,v4).x, 0.00001f);
    CHECK_CLOSE (0,        cross(v1,v4).y, 0.00001f);
    CHECK_CLOSE (0,        cross(v1,v4).z, 0.00001f);
    CHECK_CLOSE (1,        cross(v1,v4).w, 0.00001f);
}


TEST (Vector_lerp)
{
    Vector v0 (10,10,0);
    Vector v1 (11,10,0);
    Vector v2 (10,11,0);

    Vector v3 = lerp (0, 0, v0, v1, v2);
    CHECK_CLOSE (10.f,   v3.x, 0.00001f);
    CHECK_CLOSE (10.f,   v3.y, 0.00001f);
    CHECK_CLOSE (0.f,    v3.z, 0.00001f);

    Vector v4 = lerp (1, 0, v0, v1, v2);
    CHECK_CLOSE (11.f,   v4.x, 0.00001f);
    CHECK_CLOSE (10.f,   v4.y, 0.00001f);
    CHECK_CLOSE (0.f,    v4.z, 0.00001f);

    Vector v5 = lerp (0, 1, v0, v1, v2);
    CHECK_CLOSE (10.f,   v5.x, 0.00001f);
    CHECK_CLOSE (11.f,   v5.y, 0.00001f);
    CHECK_CLOSE (0.f,    v5.z, 0.00001f);

    Vector v6 = lerp (0.5, 0.5, v0, v1, v2);
    CHECK_CLOSE (10.5f,  v6.x, 0.00001f);
    CHECK_CLOSE (10.5f,  v6.y, 0.00001f);
    CHECK_CLOSE (0.f,    v6.z, 0.00001f);
}

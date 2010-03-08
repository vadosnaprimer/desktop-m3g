#include <unittest++/UnitTest++.h>
#include <iostream>
#include "Matrix.hpp"
#include "Vector.hpp"
using namespace std;
using namespace m3g;

TEST (Matrix_new)
{
  float m[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
  Matrix mat (m);
  
  CHECK_EQUAL (0.f, mat.m[0][0]);
  CHECK_EQUAL (1.f, mat.m[0][1]);
  CHECK_EQUAL (2.f, mat.m[0][2]);
  CHECK_EQUAL (3.f, mat.m[0][3]);
  CHECK_EQUAL (4.f, mat.m[1][0]);
  CHECK_EQUAL (5.f, mat.m[1][1]);
  CHECK_EQUAL (6.f, mat.m[1][2]);
  CHECK_EQUAL (7.f, mat.m[1][3]);
  CHECK_EQUAL (8.f, mat.m[2][0]);
  CHECK_EQUAL (9.f, mat.m[2][1]);
  CHECK_EQUAL (10.f, mat.m[2][2]);
  CHECK_EQUAL (11.f, mat.m[2][3]);
  CHECK_EQUAL (12.f, mat.m[3][0]);
  CHECK_EQUAL (13.f, mat.m[3][1]);
  CHECK_EQUAL (14.f, mat.m[3][2]);
  CHECK_EQUAL (15.f, mat.m[3][3]);
}

TEST (Matrix_setIdentity)
{
  Matrix mat;

  CHECK_EQUAL (1.f, mat.m[0][0]);
  CHECK_EQUAL (1.f, mat.m[1][1]);
  CHECK_EQUAL (1.f, mat.m[2][2]);
  CHECK_EQUAL (1.f, mat.m[3][3]);
  CHECK_EQUAL (0.f, mat.m[1][0]);
  CHECK_EQUAL (0.f, mat.m[0][1]);
  CHECK_EQUAL (0.f, mat.m[3][0]);
  CHECK_EQUAL (0.f, mat.m[2][3]);
  
  mat.setIdentity();

  CHECK_EQUAL (1.f, mat.m[0][0]);
  CHECK_EQUAL (1.f, mat.m[1][1]);
  CHECK_EQUAL (1.f, mat.m[2][2]);
  CHECK_EQUAL (1.f, mat.m[3][3]);
  CHECK_EQUAL (0.f, mat.m[1][0]);
  CHECK_EQUAL (0.f, mat.m[0][1]);
  CHECK_EQUAL (0.f, mat.m[3][0]);
  CHECK_EQUAL (0.f, mat.m[2][3]);
}

TEST (Matrix_setRotate)
{
    Matrix mat;
    Vector v;

    mat.setRotate (90, 1,0,0);

    Vector v0 = mat * Vector(0,1,0);
    
    CHECK_CLOSE (0.f, v0[0], 0.00001);
    CHECK_CLOSE (0.f, v0[1], 0.00001);
    CHECK_CLOSE (1.f, v0[2], 0.00001);

    mat.setRotate (90, 0,1,0);
    Vector v1 = mat * Vector(1,0,0);
  
    CHECK_CLOSE (0.f, v1[0], 0.00001);
    CHECK_CLOSE (0.f, v1[1], 0.00001);
    CHECK_CLOSE (-1.f, v1[2], 0.00001);

    mat.setRotate (90, -1,0,0);
    Vector v2 = mat * Vector (0,0,-1);

    CHECK_CLOSE (0.f, v2[0], 0.00001);
    CHECK_CLOSE (-1.f, v2[1], 0.00001);
    CHECK_CLOSE (0.f, v2[2], 0.00001);
  
}

TEST (Matrix_setScale)
{
    Matrix mat;
    mat.setScale (2,3,4);

    Vector v = mat * Vector(1,2,3);
    
    CHECK_CLOSE (2.f, v[0], 0.00001);
    CHECK_CLOSE (6.f, v[1], 0.00001);
    CHECK_CLOSE (12.f, v[2], 0.00001);

}

TEST (Matrix_setTranslate)
{
  Matrix mat;
  mat.setTranslate (2,5,8);
  Vector r = mat * Vector(1,2,3);

  CHECK_CLOSE (3, r[0], 0.00001);
  CHECK_CLOSE (7, r[1], 0.00001);
  CHECK_CLOSE (11, r[2], 0.00001);

}

TEST (Matrix_invert)
{
  Matrix m (1, 2, 3, 4,  
	    0, 2, 4, 6,  
	    3, 1, 3, 1,  
	    -1, 1, 0, -1);
  m.invert();

    //    0.6666667  - 0.5      8.327D-17  - 0.3333333  
    //    1.0833333  - 0.625  - 0.25         0.3333333  
    //  - 1.1666667    0.75     0.5          0.3333333  
    //    0.4166667  - 0.125  - 0.25       - 0.3333333  

  CHECK_CLOSE (0.6666667f, m.m[0][0], 0.00001);
  CHECK_CLOSE (-0.625f,    m.m[1][1], 0.00001);
  CHECK_CLOSE (0.4166667f, m.m[3][0], 0.00001);
  CHECK_CLOSE (0.3333333f, m.m[2][3], 0.00001);
}

TEST (Matrix_transpose)
{
  Matrix m (1, 2, 3, 4,  
	    0, 2, 4, 6,  
	    3, 1, 3, 1,  
	    -1, 1, 0, -1);
  m.transpose();

  //    1.    0.    3.  - 1.  
  //    2.    2.    1.    1.  
  //    3.    4.    3.    0.  
  //    4.    6.    1.  - 1.  
 
  CHECK_CLOSE (1.f, m.m[0][0], 0.00001);
  CHECK_CLOSE (2.f, m.m[1][1], 0.00001);
  CHECK_CLOSE (4.f, m.m[3][0], 0.00001);
  CHECK_CLOSE (0.f, m.m[2][3], 0.00001);
}

 
TEST (Matrix_multiply)
{
  Matrix m0 (1,2,3,4,
	     5,6,7,8,
	     1,2,3,4,
	     5,6,7,8);
  Matrix m1 (1,2,1,2,
	     -1,0,-1,0,
	     1,1,-1,-1,
	     1,2,3,4);
  Matrix m2 (1,1,1,1,
	     2,2,2,2,
	     3,3,3,3,
	     4,4,4,4);

  m2 *= m0;
  Matrix m3 = m0 * m1;
  
  //    12.    16.    20.    24.  
  //    24.    32.    40.    48.  
  //    36.    48.    60.    72.  
  //    48.    64.    80.    96. 
  CHECK_CLOSE (12.f, m2.m[0][0], 0.0001);
  CHECK_CLOSE (80.f, m2.m[3][2], 0.0001);


  //    6.     13.    8.     15.  
  //    14.    33.    16.    35.  
  //    6.     13.    8.     15.  
  //    14.    33.    16.    35.  
 
  CHECK_CLOSE (6.f, m3.m[0][0], 0.0001);
  CHECK_CLOSE (16.f, m3.m[3][2], 0.0001);
}

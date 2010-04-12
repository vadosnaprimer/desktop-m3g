#include "Matrix.hpp"
#include "Vector.hpp"
#include "Exception.hpp"
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;
using namespace m3g;


Matrix:: Matrix ()
{
  setIdentity();
}

Matrix:: Matrix (float* n)
{
  m[0][0] = n[0];  m[0][1] = n[1];  m[0][2] = n[2];  m[0][3] = n[3];
  m[1][0] = n[4];  m[1][1] = n[5];  m[1][2] = n[6];  m[1][3] = n[7];
  m[2][0] = n[8];  m[2][1] = n[9];  m[2][2] = n[10]; m[2][3] = n[11];
  m[3][0] = n[12]; m[3][1] = n[13]; m[3][2] = n[14]; m[3][3] = n[15];
}

Matrix:: Matrix (float m00, float m01, float m02, float m03, 
		 float m10, float m11, float m12, float m13, 
		 float m20, float m21, float m22, float m23, 
		 float m30, float m31, float m32, float m33)
{
  m[0][0] = m00;    m[0][1] = m01;    m[0][2] = m02;    m[0][3] = m03;
  m[1][0] = m10;    m[1][1] = m11;    m[1][2] = m12;    m[1][3] = m13;
  m[2][0] = m20;    m[2][1] = m21;    m[2][2] = m22;    m[2][3] = m23;
  m[3][0] = m30;    m[3][1] = m31;    m[3][2] = m32;    m[3][3] = m33;
}

Matrix:: ~Matrix ()
{
}

void Matrix:: set(const float* mat)
{
  memcpy (m, mat, sizeof(m));
}

void Matrix:: setIdentity()
{
  m[0][0] = m[0][1] = m[0][2] = m[0][3] = 0;
  m[1][0] = m[1][1] = m[1][2] = m[1][3] = 0;
  m[2][0] = m[2][1] = m[2][2] = m[2][3] = 0;
  m[3][0] = m[3][1] = m[3][2] = m[3][3] = 0;
  m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
}

void Matrix:: setRotate (float angle, float ax, float ay, float az)
{
  angle = 2*M_PI*angle/360.f;

  float c = cosf(angle);
  float s = sinf(angle);

  m[0][0] = ax*ax*(1-c)+c;
  m[0][1] = ax*ay*(1-c)-az*s;
  m[0][2] = ax*az*(1-c)+ay*s;
  m[0][3] = 0;
  m[1][0] = ay*ax*(1-c)+az*s;
  m[1][1] = ay*ay*(1-c)+c;
  m[1][2] = ay*az*(1-c)-ax*s;
  m[1][3] = 0;
  m[2][0] = ax*az*(1-c)-ay*s;
  m[2][1] = ay*az*(1-c)+ax*s;
  m[2][2] = az*az*(1-c)+c;
  m[2][3] = 0;
  m[3][0] = 0;
  m[3][1] = 0;
  m[3][2] = 0;
  m[3][3] = 1;


}

void Matrix:: setScale (float sx, float sy, float sz)
{
  setIdentity();

  m[0][0] = sx;
  m[1][1] = sy;
  m[2][2] = sz;
}

void Matrix:: setTranslate (float tx, float ty, float tz)
{
  setIdentity();

  m[0][3] = tx;
  m[1][3] = ty;
  m[2][3] = tz;
}

Matrix Matrix:: invert ()
{
  float n[4][4];
  memcpy (n, m, sizeof(m));

  float det = 
    + n[0][0]*n[1][1]*n[2][2]*n[3][3] + n[0][0]*n[1][2]*n[2][3]*n[3][1] + n[0][0]*n[1][3]*n[2][1]*n[3][2]
    + n[0][1]*n[1][0]*n[2][3]*n[3][2] + n[0][1]*n[1][2]*n[2][0]*n[3][3] + n[0][1]*n[1][3]*n[2][2]*n[3][0]
    + n[0][2]*n[1][0]*n[2][1]*n[3][3] + n[0][2]*n[1][1]*n[2][3]*n[3][0] + n[0][2]*n[1][3]*n[2][0]*n[3][1]
    + n[0][3]*n[1][0]*n[2][2]*n[3][1] + n[0][3]*n[1][1]*n[2][0]*n[3][2] + n[0][3]*n[1][2]*n[2][1]*n[3][0]
    - n[0][0]*n[1][1]*n[2][3]*n[3][2] - n[0][0]*n[1][2]*n[2][1]*n[3][3] - n[0][0]*n[1][3]*n[2][2]*n[3][1]
    - n[0][1]*n[1][0]*n[2][2]*n[3][3] - n[0][1]*n[1][2]*n[2][3]*n[3][0] - n[0][1]*n[1][3]*n[2][0]*n[3][2]
    - n[0][2]*n[1][0]*n[2][3]*n[3][1] - n[0][2]*n[1][1]*n[2][0]*n[3][3] - n[0][2]*n[1][3]*n[2][1]*n[3][0]
    - n[0][3]*n[1][0]*n[2][1]*n[3][2] - n[0][3]*n[1][1]*n[2][2]*n[3][0] - n[0][3]*n[1][2]*n[2][0]*n[3][1];

  if (det == 0) {
    throw IllegalArgumentException (__FILE__, __func__, "Can't invert this matrix.");
  }

  float inv_det = 1/det;

  m[0][0] = inv_det*(n[1][1]*n[2][2]*n[3][3] + n[1][2]*n[2][3]*n[3][1] + n[1][3]*n[2][1]*n[3][2] - n[1][1]*n[2][3]*n[3][2] - n[1][2]*n[2][1]*n[3][3] - n[1][3]*n[2][2]*n[3][1]);
  m[0][1] = inv_det*(n[0][1]*n[2][3]*n[3][2] + n[0][2]*n[2][1]*n[3][3] + n[0][3]*n[2][2]*n[3][1] - n[0][1]*n[2][2]*n[3][3] - n[0][2]*n[2][3]*n[3][1] - n[0][3]*n[2][1]*n[3][2]);
  m[0][2] = inv_det*(n[0][1]*n[1][2]*n[3][3] + n[0][2]*n[1][3]*n[3][1] + n[0][3]*n[1][1]*n[3][2] - n[0][1]*n[1][3]*n[3][2] - n[0][2]*n[1][1]*n[3][3] - n[0][3]*n[1][2]*n[3][1]);
  m[0][3] = inv_det*(n[0][1]*n[1][3]*n[2][2] + n[0][2]*n[1][1]*n[2][3] + n[0][3]*n[1][2]*n[2][1] - n[0][1]*n[1][2]*n[2][3] - n[0][2]*n[1][3]*n[2][1] - n[0][3]*n[1][1]*n[2][2]);
  m[1][0] = inv_det*(n[1][0]*n[2][3]*n[3][2] + n[1][2]*n[2][0]*n[3][3] + n[1][3]*n[2][2]*n[3][0] - n[1][0]*n[2][2]*n[3][3] - n[1][2]*n[2][3]*n[3][0] - n[1][3]*n[2][0]*n[3][2]);
  m[1][1] = inv_det*(n[0][0]*n[2][2]*n[3][3] + n[0][2]*n[2][3]*n[3][0] + n[0][3]*n[2][0]*n[3][2] - n[0][0]*n[2][3]*n[3][2] - n[0][2]*n[2][0]*n[3][3] - n[0][3]*n[2][2]*n[3][0]);
  m[1][2] = inv_det*(n[0][0]*n[1][3]*n[3][2] + n[0][2]*n[1][0]*n[3][3] + n[0][3]*n[1][2]*n[3][0] - n[0][0]*n[1][2]*n[3][3] - n[0][2]*n[1][3]*n[3][0] - n[0][3]*n[1][0]*n[3][2]);
  m[1][3] = inv_det*(n[0][0]*n[1][2]*n[2][3] + n[0][2]*n[1][3]*n[2][0] + n[0][3]*n[1][0]*n[2][2] - n[0][0]*n[1][3]*n[2][2] - n[0][2]*n[1][0]*n[2][3] - n[0][3]*n[1][2]*n[2][0]);
  m[2][0] = inv_det*(n[1][0]*n[2][1]*n[3][3] + n[1][1]*n[2][3]*n[3][0] + n[1][3]*n[2][0]*n[3][1] - n[1][0]*n[2][3]*n[3][1] - n[1][1]*n[2][0]*n[3][3] - n[1][3]*n[2][1]*n[3][0]);
  m[2][1] = inv_det*(n[0][0]*n[2][3]*n[3][1] + n[0][1]*n[2][0]*n[3][3] + n[0][3]*n[2][1]*n[3][0] - n[0][0]*n[2][1]*n[3][3] - n[0][1]*n[2][3]*n[3][0] - n[0][3]*n[2][0]*n[3][1]);
  m[2][2] = inv_det*(n[0][0]*n[1][1]*n[3][3] + n[0][1]*n[1][3]*n[3][0] + n[0][3]*n[1][0]*n[3][1] - n[0][0]*n[1][3]*n[3][1] - n[0][1]*n[1][0]*n[3][3] - n[0][3]*n[1][1]*n[3][0]);
  m[2][3] = inv_det*(n[0][0]*n[1][3]*n[2][1] + n[0][1]*n[1][0]*n[2][3] + n[0][3]*n[1][1]*n[2][0] - n[0][0]*n[1][1]*n[2][3] - n[0][1]*n[1][3]*n[2][0] - n[0][3]*n[1][0]*n[2][1]);
  m[3][0] = inv_det*(n[1][0]*n[2][2]*n[3][1] + n[1][1]*n[2][0]*n[3][2] + n[1][2]*n[2][1]*n[3][0] - n[1][0]*n[2][1]*n[3][2] - n[1][1]*n[2][2]*n[3][0] - n[1][2]*n[2][0]*n[3][1]);
  m[3][1] = inv_det*(n[0][0]*n[2][1]*n[3][2] + n[0][1]*n[2][2]*n[3][0] + n[0][2]*n[2][0]*n[3][1] - n[0][0]*n[2][2]*n[3][1] - n[0][1]*n[2][0]*n[3][2] - n[0][2]*n[2][1]*n[3][0]);
  m[3][2] = inv_det*(n[0][0]*n[1][2]*n[3][1] + n[0][1]*n[1][0]*n[3][2] + n[0][2]*n[1][1]*n[3][0] - n[0][0]*n[1][1]*n[3][2] - n[0][1]*n[1][2]*n[3][0] - n[0][2]*n[1][0]*n[3][1]);
  m[3][3] = inv_det*(n[0][0]*n[1][1]*n[2][2] + n[0][1]*n[1][2]*n[2][0] + n[0][2]*n[1][0]*n[2][1] - n[0][0]*n[1][2]*n[2][1] - n[0][1]*n[1][0]*n[2][2] - n[0][2]*n[1][1]*n[2][0]);
  
  return *this;
}

void Matrix:: transpose ()
{
  float n[4][4];
  memcpy (&n, &m, sizeof(m));

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      m[i][j] = n[j][i];
    }
  }
}

Matrix& Matrix:: operator*= (const Matrix& rhs)
{
  float m1[4][4];
  float m2[4][4];

  memcpy (m1, m, sizeof(m));
  memcpy (m2, rhs.m, sizeof(rhs.m));

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      m[i][j] = 0;
      for (int k = 0; k < 4; k++) {
	m[i][j] += m1[i][k] * m2[k][j];
      }
    }
  }
  return *this;
}

 Matrix operator* (const Matrix& lhs, const Matrix& rhs)
{
  Matrix r;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      r.m[i][j] = 0;
      for (int k = 0; k < 4; k++) {
          r.m[i][j] += lhs.m[i][k] * rhs.m[k][j];
      }
    }
  }
  return r;
}


Vector operator* (const Matrix& m, const Vector& v)
{
  Vector r(0,0,0,0);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      r[i] += m.m[i][j] * v[j];
    }
  }
  return r;
}



std::ostream& Matrix:: print (std::ostream& out) const
{
  out << "[ ";
  for (int i = 0; i < 4; i++) {
    out << "[";
    for  (int j = 0; j < 4; j++) {
      if (j == 3)
	out << m[i][j] << "] ";
      else
	out << m[i][j] << ", ";
    }
    out << "]";
  }
  return out; 
}

std::ostream& operator<< (std::ostream& out, const Matrix& mat)
{
  return mat.print(out);
}

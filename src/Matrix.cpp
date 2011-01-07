#include "m3g/Matrix.hpp"
#include "m3g/Vector.hpp"
#include "m3g/Exception.hpp"
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
    for (int i = 0; i < 16; i++) {
        m[i] = n[i];
    }
}

Matrix:: Matrix (float m00, float m01, float m02, float m03, 
                 float m10, float m11, float m12, float m13, 
                 float m20, float m21, float m22, float m23, 
                 float m30, float m31, float m32, float m33)
{
    m[0]  = m00;  m[1]  = m01;  m[2]  = m02;  m[3]  = m03;
    m[4]  = m10;  m[5]  = m11;  m[6]  = m12;  m[7]  = m13;
    m[8]  = m20;  m[9]  = m21;  m[10] = m22;  m[11] = m23;
    m[12] = m30;  m[13] = m31;  m[14] = m32;  m[15] = m33;
}

Matrix:: ~Matrix ()
{
}

Matrix Matrix:: getInverse () const
{
    Matrix mat = *this;
    return mat.invert();
}

Matrix Matrix:: get3x3 () const
{
    Matrix mat = *this;
    mat[3]  = mat[7]  = mat[11] = 0;
    mat[12] = mat[13] = mat[14] = 0;
    mat[15] = 1;
    return mat;
}


void Matrix:: set(const float* mat)
{
    memcpy (m, mat, sizeof(float)*16);
}


void Matrix:: setIdentity()
{
    m[0]  = 1;  m[1]  = 0;  m[2]  = 0;  m[3]  = 0;
    m[4]  = 0;  m[5]  = 1;  m[6]  = 0;  m[7]  = 0;
    m[8]  = 0;  m[9]  = 0;  m[10] = 1;  m[11] = 0;
    m[12] = 0;  m[13] = 0;  m[14] = 0;  m[15] = 1;
}

void Matrix:: setRotate (float angle, float ax, float ay, float az)
{
    angle = 2*M_PI*angle/360.f;

    float c = cosf(angle);
    float s = sinf(angle);

    m[0] = ax*ax*(1-c)+c;
    m[1] = ax*ay*(1-c)-az*s;
    m[2] = ax*az*(1-c)+ay*s;
    m[3] = 0;
    m[4] = ay*ax*(1-c)+az*s;
    m[5] = ay*ay*(1-c)+c;
    m[6] = ay*az*(1-c)-ax*s;
    m[7] = 0;
    m[8] = ax*az*(1-c)-ay*s;
    m[9] = ay*az*(1-c)+ax*s;
    m[10] = az*az*(1-c)+c;
    m[11] = 0;
    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
}

void Matrix:: setScale (float sx, float sy, float sz)
{
    m[0] = sx;
    m[5] = sy;
    m[10] = sz;
}

void Matrix:: setTranslate (float tx, float ty, float tz)
{
    m[3] = tx;
    m[7] = ty;
    m[11] = tz;
}

Matrix& Matrix:: invert ()
{
    float n[16];
    memcpy (n, m, sizeof(float)*16);

    float det = 
        + n[0]*n[5]*n[10]*n[15] + n[0]*n[6]*n[11]*n[13] + n[0]*n[7]*n[9 ]*n[14]
        + n[1]*n[4]*n[11]*n[14] + n[1]*n[6]*n[8 ]*n[15] + n[1]*n[7]*n[10]*n[12]
        + n[2]*n[4]*n[9 ]*n[15] + n[2]*n[5]*n[11]*n[12] + n[2]*n[7]*n[8 ]*n[13]
        + n[3]*n[4]*n[10]*n[13] + n[3]*n[5]*n[8 ]*n[14] + n[3]*n[6]*n[9 ]*n[12]
        - n[0]*n[5]*n[11]*n[14] - n[0]*n[6]*n[9 ]*n[15] - n[0]*n[7]*n[10]*n[13]
        - n[1]*n[4]*n[10]*n[15] - n[1]*n[6]*n[11]*n[12] - n[1]*n[7]*n[8 ]*n[14]
        - n[2]*n[4]*n[11]*n[13] - n[2]*n[5]*n[8 ]*n[15] - n[2]*n[7]*n[9 ]*n[12]
        - n[3]*n[4]*n[9 ]*n[14] - n[3]*n[5]*n[10]*n[12] - n[3]*n[6]*n[8 ]*n[13];

    if (det == 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Can't invert this matrix.");
    }

    float inv_det = 1/det;

    m[0]  = inv_det*(n[5]*n[10]*n[15] + n[6]*n[11]*n[13] + n[7]*n[9 ]*n[14] - n[5]*n[11]*n[14] - n[6]*n[9 ]*n[15] - n[7]*n[10]*n[13]);
    m[1]  = inv_det*(n[1]*n[11]*n[14] + n[2]*n[9 ]*n[15] + n[3]*n[10]*n[13] - n[1]*n[10]*n[15] - n[2]*n[11]*n[13] - n[3]*n[9 ]*n[14]);
    m[2]  = inv_det*(n[1]*n[6 ]*n[15] + n[2]*n[7 ]*n[13] + n[3]*n[5 ]*n[14] - n[1]*n[7 ]*n[14] - n[2]*n[5 ]*n[15] - n[3]*n[6 ]*n[13]);
    m[3]  = inv_det*(n[1]*n[7 ]*n[10] + n[2]*n[5 ]*n[11] + n[3]*n[6 ]*n[9 ] - n[1]*n[6 ]*n[11] - n[2]*n[7 ]*n[9 ] - n[3]*n[5 ]*n[10]);
    m[4]  = inv_det*(n[4]*n[11]*n[14] + n[6]*n[8 ]*n[15] + n[7]*n[10]*n[12] - n[4]*n[10]*n[15] - n[6]*n[11]*n[12] - n[7]*n[8 ]*n[14]);
    m[5]  = inv_det*(n[0]*n[10]*n[15] + n[2]*n[11]*n[12] + n[3]*n[8 ]*n[14] - n[0]*n[11]*n[14] - n[2]*n[8 ]*n[15] - n[3]*n[10]*n[12]);
    m[6]  = inv_det*(n[0]*n[7 ]*n[14] + n[2]*n[4 ]*n[15] + n[3]*n[6 ]*n[12] - n[0]*n[6 ]*n[15] - n[2]*n[7 ]*n[12] - n[3]*n[4 ]*n[14]);
    m[7]  = inv_det*(n[0]*n[6 ]*n[11] + n[2]*n[7 ]*n[8 ] + n[3]*n[4 ]*n[10] - n[0]*n[7 ]*n[10] - n[2]*n[4 ]*n[11] - n[3]*n[6 ]*n[8 ]);
    m[8]  = inv_det*(n[4]*n[9 ]*n[15] + n[5]*n[11]*n[12] + n[7]*n[8 ]*n[13] - n[4]*n[11]*n[13] - n[5]*n[8 ]*n[15] - n[7]*n[9 ]*n[12]);
    m[9]  = inv_det*(n[0]*n[11]*n[13] + n[1]*n[8 ]*n[15] + n[3]*n[9 ]*n[12] - n[0]*n[9 ]*n[15] - n[1]*n[11]*n[12] - n[3]*n[8 ]*n[13]);
    m[10] = inv_det*(n[0]*n[5 ]*n[15] + n[1]*n[7 ]*n[12] + n[3]*n[4 ]*n[13] - n[0]*n[7 ]*n[13] - n[1]*n[4 ]*n[15] - n[3]*n[5 ]*n[12]);
    m[11] = inv_det*(n[0]*n[7 ]*n[9 ] + n[1]*n[4 ]*n[11] + n[3]*n[5 ]*n[8 ] - n[0]*n[5 ]*n[11] - n[1]*n[7 ]*n[8 ] - n[3]*n[4 ]*n[9 ]);
    m[12] = inv_det*(n[4]*n[10]*n[13] + n[5]*n[8 ]*n[14] + n[6]*n[9 ]*n[12] - n[4]*n[9 ]*n[14] - n[5]*n[10]*n[12] - n[6]*n[8 ]*n[13]);
    m[13] = inv_det*(n[0]*n[9 ]*n[14] + n[1]*n[10]*n[12] + n[2]*n[8 ]*n[13] - n[0]*n[10]*n[13] - n[1]*n[8 ]*n[14] - n[2]*n[9 ]*n[12]);
    m[14] = inv_det*(n[0]*n[6 ]*n[13] + n[1]*n[4 ]*n[14] + n[2]*n[5 ]*n[12] - n[0]*n[5 ]*n[14] - n[1]*n[6 ]*n[12] - n[2]*n[4 ]*n[13]);
    m[15] = inv_det*(n[0]*n[5 ]*n[10] + n[1]*n[6 ]*n[8 ] + n[2]*n[4 ]*n[9 ] - n[0]*n[6 ]*n[9 ] - n[1]*n[4 ]*n[10] - n[2]*n[5 ]*n[8 ]);
  
    return *this;
}

Matrix& Matrix:: transpose ()
{
    float n[16];
    memcpy (n, m, sizeof(float)*16);

    m[0] = n[0];
    m[1] = n[4];
    m[2] = n[8];
    m[3] = n[12];

    m[4] = n[1];
    m[5] = n[5];
    m[6] = n[9];
    m[7] = n[13];

    m[8]  = n[2];
    m[9]  = n[6];
    m[10] = n[10];
    m[11] = n[14];

    m[12] = n[3];
    m[13] = n[7];
    m[14] = n[11];
    m[15] = n[15];

    return *this;
}

Matrix& Matrix:: operator*= (const Matrix& rhs)
{
    // this = this * rhs;
    float m1[16];
    float m2[16];

    memcpy (m1, m, sizeof(float)*16);
    memcpy (m2, rhs.m, sizeof(float)*16);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m[i*4+j] = 0;
            for (int k = 0; k < 4; k++) {
                m[i*4+j] += m1[i*4+k] * m2[k*4+j];
            }
        }
    }
    return *this;
}

float& Matrix:: operator[] (int n)
{
    if (n < 0 || n > 15) {
        throw IndexOutOfBoundsException (__FILE__, __func__, "Index is invalid, i=%d.", n);
    }
    return m[n];
}

const float& Matrix:: operator[] (int n) const
{
    if (n < 0 || n > 15) {
        throw IndexOutOfBoundsException (__FILE__, __func__, "Index is invalid, i=%d.", n);
    }
    return m[n];
}

Matrix operator* (const Matrix& lhs, const Matrix& rhs)
{
    Matrix r = lhs;
    r *= rhs;
    return r;
}


Vector operator* (const Matrix& m, const Vector& v)
{
    Vector r(0,0,0,0);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            r[i] += m.m[i*4+j] * v[j];
        }
    }
    return r;
}


Matrix m3g:: make_parallel_projection_matrix    (float height, float aspect_ratio, float near, float far)
{
    float  width = height * aspect_ratio;
    Matrix proj;
    proj[0]  = 2/width;
    proj[5]  = 2/height;
    proj[10] = -2/(far-near);
    proj[11] = -(near+far)/(far-near);
    proj[15] = 1;
    return proj;
}

Matrix m3g:: make_perspective_projection_matrix (float fovy, float aspect_ratio, float near, float far)
{
    fovy = fovy*2*M_PI/360.f;

    float  height = tanf (fovy/2.f);
    float  width  = height * aspect_ratio;
    Matrix proj;
    proj[0]  = 1/width;
    proj[5]  = 1/height;
    proj[10] = -(near+far)/(far-near);
    proj[11] = -2*near*far/(far-near);
    proj[14] = -1;
    proj[15] = 0;
    return proj;
}

std::ostream& Matrix:: print (std::ostream& out) const
{
    out << "[ " << m[0] << "," << m[1] << "," << m[2] << "," << m[3] << ";";
    out << " " << m[4] << "," << m[5] << "," << m[6] << "," << m[7] << ";";
    out << " " << m[8] << "," << m[9] << "," << m[10] << "," << m[11] << ";";
    out << " " << m[12] << "," << m[13] << "," << m[14] << "," << m[15] << " ]";
    return out; 
}

std::ostream& operator<< (std::ostream& out, const Matrix& mat)
{
    return mat.print(out);
}

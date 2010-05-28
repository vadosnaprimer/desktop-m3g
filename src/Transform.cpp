#include "Transform.hpp"
#include "Vector.hpp"
#include "Exception.hpp"
#include "Quaternion.hpp"
#include "Vector.hpp"
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
using namespace m3g;


Transform:: Transform ()
{
}

Transform:: Transform (const Transform& t)
{
    matrix = t.matrix;
}

Transform:: ~Transform ()
{
}

void Transform:: get (float* mat) const
{
    if (mat == NULL) {
        throw NullPointerException (__FILE__, __func__, "Matrix is NULL.");
    }
    memcpy (mat, &matrix.m, sizeof(matrix.m));
}

Matrix Transform:: getMatrix () const
{
    return matrix;
}

void Transform:: invert ()
{
    matrix.invert ();
}

void Transform:: postMultiply (const Transform& t)
{
    matrix *= t.matrix;
}

void Transform:: postRotate (float angle, float ax, float ay, float az)
{
    float len2 = ax*ax+ay*ay+az*az;
    if (len2 != 1.f) {
        float len = sqrtf(len2);
        ax /= len;
        ay /= len;
        az /= len;
    }

    Matrix rotate;
    rotate.setRotate (angle, ax, ay, az);

    matrix *= rotate;
}

void Transform:: postRotateQuat (float qx, float qy, float qz, float qw)
{
    Quaternion q;
    q.set (qx, qy, qz, qw);

    float a[4];
    q.getAngleAxis (a);

    Matrix rotate;
    rotate.setRotate (a[0], a[1], a[2], a[3]);
  
    matrix *= rotate;
}

void Transform:: postScale (float sx, float sy, float sz)
{
    Matrix scale;
    scale.setScale (sx, sy, sz);

    matrix *= scale;
}

void Transform:: postTranslate (float tx, float ty, float tz)
{
    Matrix translate;
    translate.setTranslate (tx, ty, tz);

    matrix *= translate;
}

void Transform:: set (const float* mat)
{
    if (mat == NULL) {
        throw NullPointerException (__FILE__, __func__, "Material is NULL.");
    }
    matrix.set (mat);
}

void Transform:: set (const Transform& t)
{
    matrix = t.matrix;
}

void Transform:: set (const Matrix& mat)
{
    matrix = mat;
}

void Transform:: setIdentity ()
{
    matrix.setIdentity();
}

void Transform:: transform (float* vectors) const
{
    if (vectors == NULL) {
        throw NullPointerException (__FILE__, __func__, "Vectors is NULL.");
    }
    Vector v (vectors[0], vectors[1], vectors[2]);

    Vector r = matrix * v;
    r.get (vectors);
}

void Transform:: transform (VertexArray* in, float* out, bool w) const
{
    // 
    // あれ実装していない？
}

Vector Transform:: transform (const Vector& v) const
{
    return matrix * v;
}


void Transform:: transpose ()
{
    matrix.transpose();
}


std::ostream& Transform:: print (std::ostream& out) const
{
    return out << matrix;
}

std::ostream& operator<< (std::ostream& out, const Transform& trns)
{
    return trns.print(out);
}





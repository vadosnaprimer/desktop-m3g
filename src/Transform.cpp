#include "m3g/Transform.hpp"
#include "m3g/Vector.hpp"
#include "m3g/Exception.hpp"
#include "m3g/Quaternion.hpp"
#include "m3g/Vector.hpp"
#include "m3g/VertexArray.hpp"
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
        throw NullPointerException (__FILE__, __func__, "Matrix is NULL.");
    }
    matrix.set (mat);
}

void Transform:: set (const Transform* t)
{
    if (t == NULL) {
        throw NullPointerException (__FILE__, __func__, "Transform is NULL.");
    }
    matrix = t->matrix;
}

void Transform:: set (const Matrix& mat)
{
    matrix = mat;
}

void Transform:: setIdentity ()
{
    matrix.setIdentity();
}

void Transform:: transform (int vector_num, float* vectors) const
{
    if (vectors == NULL) {
        throw NullPointerException (__FILE__, __func__, "Vectors is NULL.");
    }
    if (vector_num < 0 || vector_num % 4 != 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Vector num is invalid. num=%d", vector_num);
    }

    for (int v = 0; v < vector_num; v+=4) {
        Vector in (vectors[v+0], vectors[v+1], vectors[v+2], vectors[v+3]);        
        Vector out = matrix * in;
        out.get4 (vectors + v);
    }



}

void Transform:: transform (const VertexArray* in, float* out, bool w) const
{
    if (in == NULL) {
        throw NullPointerException (__FILE__, __func__, "VertexArray is NULL.");
    }
    if (out == NULL) {
        throw NullPointerException (__FILE__, __func__, "Out values is NULL.");
    }
    if (in->getComponentCount() == 4) {
        throw IllegalArgumentException (__FILE__, __func__, "Component count must be 2 or 3.");
    }

    float scale   = 1;
    float bias[4] = {0,0,0,0};

    for (int v = 0; v < (int)in->getVertexCount(); v++) {
        float* values = out + v*4;
        values[0] = values[1] = values[2] = 0;
        values[3] = w ? 1 : 0;
        in->get (v, 1, scale, bias, values);
        transform (4, values);
    }
}

Vector Transform:: transform (const Vector& v) const
{
    return matrix * v;
}

Vector Transform:: transform3x3 (const Vector& v) const
{
    return matrix.get3x3() * v;
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





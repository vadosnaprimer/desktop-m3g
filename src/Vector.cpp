#include "m3g/Vector.hpp"
#include "m3g/Exception.hpp"
#include "m3g/m3ginternal.hpp"
#include <iostream>
#include <cmath>
using namespace std;
using namespace m3g;


Vector:: Vector () : x(0), y(0), z(0), w(1)
{
}

Vector:: Vector (float* xyz) : x(0), y(0), z(0), w(1)
{
    x = xyz[0];
    y = xyz[1];
    z = xyz[2];
    w = 1;
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
    if (w != 0) {
        xyz[0] = x/w; 
        xyz[1] = y/w;
        xyz[2] = z/w;
    } else {
        xyz[0] = x;
        xyz[1] = y;
        xyz[2] = z;
    }
}

void Vector:: get4 (float* xyzw) const
{
    xyzw[0] = x;
    xyzw[1] = y;
    xyzw[2] = z;
    xyzw[3] = w;
}

float Vector:: length () const
{
    if (w == 0) {
        throw ArithmeticException (__FILE__, __func__, "Lenght of vector, but w is 0.");
    }
    return sqrtf ((x*x+y*y+z*z)/(w*w));
}

float& Vector:: operator[] (int index)
{
    if (index < 0 || index > 3) {
        throw IndexOutOfBoundsException (__FILE__, __func__, "Index is invalid, index=%d.", index);
    }
    return (&x)[index];
}

const float& Vector:: operator[] (int index) const
{
    if (index < 0 || index > 3) {
        throw IndexOutOfBoundsException (__FILE__, __func__, "Index is invalid, index=%d.", index);
    }
    return (&x)[index];
}

Vector Vector:: operator- () const
{
    Vector v;
    v.x = -x;
    v.y = -y;
    v.z = -z;
    v.w =  w;
    return v;
}


Vector& Vector:: operator+= (const Vector& rhs)
{
    if (rhs.w == 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Divided by 0.");
    }

    x += rhs.x * w/rhs.w;
    y += rhs.y * w/rhs.w;
    z += rhs.z * w/rhs.w;
    return *this;
}


Vector& Vector:: normalize ()
{
    float len = length();
    if (len == 0) {
        throw ArithmeticException (__FILE__, __func__, "Normalized, but length of vector is 0.");
    }
    x /= len;
    y /= len;
    z /= len;
    return *this;
}

Vector& Vector:: divided_by_w ()
{
    if (w == 0) {
        throw ArithmeticException (__FILE__, __func__, "Divied by w=0.");
    }
    x /= w;
    y /= w;
    z /= w;
    w =  1;
    return *this;
}


float m3g::dot (const Vector& p, const Vector& q)
{
    if (fabsf(p.w-1) > M3G_EPSILON || fabsf(q.w-1) > M3G_EPSILON) {
        throw ArithmeticException (__FILE__, __func__, "Dot, but w is not 1. p.w=%f, q.w=%f.", p.w, q.w);
    }
    return p.x*q.x+p.y*q.y+p.z*q.z;
}

Vector m3g::cross (const Vector& p, const Vector& q)
{
    if (p.w != 1 || q.w != 1) {
        throw ArithmeticException (__FILE__, __func__, "Cross, but w is not 1. p.w=%f, q.w=%f.", p.w, q.w);
    }
    return Vector (p.y*q.z-p.z*q.y, p.z*q.x-p.x*q.z, p.x*q.y-p.y*q.x);
}

Vector m3g::lerp (float u, float v, const Vector& v0, const Vector& v1, const Vector& v2)
{
    if (v0.w != 1 || v1.w != 1 || v2.w != 1) {
        throw ArithmeticException (__FILE__, __func__, "lerp, w must be 1, v0.w=%f, v1.w=%f, v2.w=%f.", v0.w, v1.w, v2.w);
    }

    Vector e1 = v1 - v0;
    Vector e2 = v2 - v0;
    return v0 + e1*u + e2*v;
}



Vector operator* (const Vector& lhs, float f)
{
    Vector v (lhs);
    v.x *= f;
    v.y *= f;
    v.z *= f;
    return v;
}

Vector operator* (float f, const Vector& rhs)
{
    return rhs*f;
}

Vector operator/ (const Vector& lhs, float f)
{
    if (f == 0) {
        throw ArithmeticException (__FILE__, __func__, "Divided by 0. in Vector/f.");
    }
    Vector v (lhs);
    v.x /= f;
    v.y /= f;
    v.z /= f;
    return v;
}

Vector operator+ (const Vector& lhs, const Vector& rhs)
{
    if (lhs.w != rhs.w && lhs.w != 0 && rhs.w != 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Add vectors with different w. lhs.w=%f, rhs.w=%f.", lhs.w, rhs.w);
    }

    if (lhs.w == rhs.w) {
        return Vector(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w);
    } else {
        return Vector(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
    }
}

m3g::Vector operator- (const m3g::Vector& lhs, const m3g::Vector& rhs)
{
    if (lhs.w != rhs.w && lhs.w != 0 && rhs.w != 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Subtracted vectors with different w. lhs.w=%f, rhs.w=%f.", lhs.w, rhs.w);
    }

    if (lhs.w == rhs.w) {
        return Vector(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w);
    } else if (lhs.w == 0) {
        return Vector(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, rhs.w);
    } else {
        return Vector(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w);
    }
}

std::ostream& Vector:: print (std::ostream& out) const
{
    return out << x << ", " << y << ", " << z << ", " << w;
}

std::ostream& operator<< (std::ostream& out , const m3g::Vector& v)
{
    return v.print (out);
}


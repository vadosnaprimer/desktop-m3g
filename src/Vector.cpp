#include "Vector.hpp"
#include "Exception.hpp"
#include "m3ginternal.hpp"
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

float m3g::dot (const Vector& p, const Vector& q)
{
    if (p.w != 1 || q.w != 1) {
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


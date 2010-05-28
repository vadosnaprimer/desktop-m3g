#include "Intersect.hpp"
#include "Vector.hpp"
#include "Exception.hpp"
#include "m3ginternal.hpp"
#include <iostream>
using namespace m3g;
using namespace std;


/**
 * バックフェースカリングを考慮する交差判定.
 */
bool m3g::triangle_intersect (const Vector& org, const Vector& dir, 
                              const Vector& v0, const Vector& v1, const Vector& v2,
                              float* u_, float* v_, float* t_)
{
    if (org.w != 1 || dir.w != 1 || v0.w != 1 || v1.w != 1 || v2.w != 1) {
        throw IllegalArgumentException (__FILE__, __func__, "W of input vectors must be 1, org.w=%f, dir.w=%f, v0.w=%f, v1.w=%f, v2.w=%f",
                                        org.w, dir.w, v0.w, v1.w, v2.w);
    }
    
    cout << "org = " << org << "\n";
    cout << "dir = " << dir << "\n";

    cout << "v0 = " << v0 << "\n";
    cout << "v1 = " << v1 << "\n";
    cout << "v2 = " << v2 << "\n";

    Vector e1 = v1 - v0;
    Vector e2 = v2 - v0;

    cout << "e1 = " << e1 << "\n";
    cout << "e2 = " << e2 << "\n";

    Vector p  = cross (dir, e2);

    cout << "p  = " << p << "\n";

    float  a  = dot (e1, p);
    cout << "a  = " << a << "\n";
    if (a < M3G_EPSILON)
        return false;

    Vector s = org - v0;
    float  u = dot (s, p);
    if (u < 0 || u > a)
        return false;


    Vector q = cross (s, e1);

    float  v = dot(dir, q);
    if (v < 0 || u+v > a)
        return false;

    float t = dot(e2, q);
    float f = 1/a;
    t *= f;
    u *= f;
    v *= f;

    if (t < 0)
        return false;

    if (u_)
        *u_ = u;
    if (v_)
        *v_ = v;
    if (t_)
        *t_ = t;
    return true;
}

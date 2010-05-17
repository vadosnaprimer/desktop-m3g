#ifndef __INTERSECT_HPP__
#define __INTERSECT_HPP__


namespace m3g {

    class Vector;

    bool triangle_intersect (const Vector& org, const Vector& dir, 
                             const Vector& v0, const Vector& v1, const Vector& v2,
                             float* u, float* v, float* d);



}


#endif


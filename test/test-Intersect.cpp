#include <unittest++/UnitTest++.h>
#include <iostream>
#include <cmath>
#include "m3g/Intersect.hpp"
#include "m3g/Vector.hpp"
using namespace std;
using namespace m3g;


TEST (Intersect_triangle_intersect)
{
    Vector v0 (0,1,0);
    Vector v1 (-1,-1,0);
    Vector v2 (1,-1,0);

    bool  hit;
    float u, v, t;

    Vector org0 (0,0,1);
    Vector dir0 (0,0,-1);
    hit = triangle_intersect (org0, dir0, v0, v1, v2, &u, &v, &t);

    CHECK_EQUAL (true, hit);
    CHECK_CLOSE (0.25f, u, 0.00001f);
    CHECK_CLOSE (0.25f, v, 0.00001f);
    CHECK_CLOSE (1.f,   t, 0.00001f);
    //cout << "intersect: hit = " << hit << ", u = " << u << ", v = " << v << ", t = " << t << "\n";

    Vector org1 (1,1,1);
    Vector dir1 (0,0,-1);
    hit = triangle_intersect (org1, dir1, v0, v1, v2, &u, &v, &t);

    CHECK_EQUAL (false, hit);
    //cout << "intersect: hit = " << hit << ", u = " << u << ", v = " << v << ", t = " << t << "\n";

    Vector org2 (-1,1,1);
    Vector dir2 (0,0,-1);
    hit = triangle_intersect (org2, dir2, v0, v1, v2, &u, &v, &t);

    CHECK_EQUAL (false, hit);
    //cout << "intersect: hit = " << hit << ", u = " << u << ", v = " << v << ", t = " << t << "\n";

    Vector org3 (0,-2,1);
    Vector dir3 (0,0,-1);
    hit = triangle_intersect (org3, dir3, v0, v1, v2, &u, &v, &t);

    CHECK_EQUAL (false, hit);
    //cout << "intersect: hit = " << hit << ", u = " << u << ", v = " << v << ", t = " << t << "\n";

    Vector org4 (0,0,-1);
    Vector dir4 (0,0,-1);
    hit = triangle_intersect (org4, dir4, v0, v1, v2, &u, &v, &t);

    CHECK_EQUAL (false, hit);
    //cout << "intersect: hit = " << hit << ", u = " << u << ", v = " << v << ", t = " << t << "\n";

    Vector org5 (0,0,1);
    Vector dir5 (1,0,0);
    hit = triangle_intersect (org5, dir5, v0, v1, v2, &u, &v, &t);

    CHECK_EQUAL (false, hit);
    //cout << "intersect: hit = " << hit << ", u = " << u << ", v = " << v << ", t = " << t << "\n";

    Vector org6 (0,0,-1);
    Vector dir6 (1,0,0);
    hit = triangle_intersect (org6, dir6, v0, v1, v2, &u, &v, &t);

    CHECK_EQUAL (false, hit);
    //cout << "intersect: hit = " << hit << ", u = " << u << ", v = " << v << ", t = " << t << "\n";


}



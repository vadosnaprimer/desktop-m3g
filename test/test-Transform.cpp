#include <unittest++/UnitTest++.h>
#include <iostream>
#include <cstdlib>
#include "Transform.hpp"
#include "Quaternion.hpp"
#include "Vector.hpp"
using namespace std;
using namespace m3g;

TEST (Transform_default_variables)
{
    Transform trs;
    float m[4][4];

    trs.get ((float*)m);

    CHECK_CLOSE (1, m[0][0], 0.00001);
    CHECK_CLOSE (0, m[1][0], 0.00001);
    CHECK_CLOSE (1, m[3][3], 0.00001);
}

TEST (Transform_get_variables)
{
    Transform trs;
    Matrix matrix (1,2,3,4,
                   5,6,7,8,
                   9,10,11,12,
                   13,14,15,16);
    
    trs.set (matrix);

    Matrix mat = trs.getMatrix();
    for (int i = 0; i < 16; i++) {
        CHECK_CLOSE (mat[i], matrix[i], 0.00001f);
    }

    float m[16];
    trs.get (m);
    for (int i = 0; i < 16; i++) {
        CHECK_CLOSE (m[i], matrix[i], 0.00001f);
    }
    
}

TEST (Transform_set_variables)
{
    Transform trs;
    float m[4][4] = {{0,2,3,4},{5,0,7,8},{9,10,0,12},{13,14,15,0}};

    trs.set ((float*)m);
    trs.get ((float*)m);
    CHECK_CLOSE (0, m[0][0], 0.00001);
    CHECK_CLOSE (5, m[1][0], 0.00001);
    CHECK_CLOSE (0, m[3][3], 0.00001);

    // - 0.2952286    0.0924453    0.0367793    0.0159046  
    //  0.1580517  - 0.1252485    0.0308151    0.0268390  
    //  0.1083499    0.0367793  - 0.0606362    0.0278330  
    //  0.0897117    0.0350398    0.0300696  - 0.0342942  
 
    trs.invert();
    trs.get ((float*)m);
    CHECK_CLOSE (-0.2952286f, m[0][0], 0.00001);
    CHECK_CLOSE ( 0.1580517f, m[1][0], 0.00001);
    CHECK_CLOSE (-0.0342942f, m[3][3], 0.00001);

    Transform trs2;
    trs2.set (trs);
    trs2.get ((float*)m);
    CHECK_CLOSE (-0.2952286f, m[0][0], 0.00001);
    CHECK_CLOSE ( 0.1580517f, m[1][0], 0.00001);
    CHECK_CLOSE (-0.0342942f, m[3][3], 0.00001);

    trs2.setIdentity();
    trs2.get ((float*)m);
    CHECK_CLOSE (1, m[0][0], 0.00001);
    CHECK_CLOSE (0, m[1][0], 0.00001);
    CHECK_CLOSE (1, m[3][3], 0.00001);
}

TEST (Transpose_post_xxx)
{
    Transform trs;


    trs.postScale (2,3,4);
    {
        float v[3] = {1,1,1};
        trs.transform (v);
    
        CHECK_CLOSE (2, v[0], 0.00001);
        CHECK_CLOSE (3, v[1], 0.00001);
        CHECK_CLOSE (4, v[2], 0.00001);
    }

    trs.postTranslate (1,1,1);
    {
        float v[3] = {1,2,3};
        trs.transform (v);
    
        CHECK_CLOSE (4, v[0], 0.00001);
        CHECK_CLOSE (9, v[1], 0.00001);
        CHECK_CLOSE (16, v[2], 0.00001);
    }

}

TEST (Transpose_post_multiply)
{

    Transform post;
    post.postScale (1,2,3);

    Transform trs;
    trs.postTranslate (1,1,1);
    trs.postMultiply (post);

    float v[3] = {3,2,1};
    trs.transform (v);

    CHECK_CLOSE (4, v[0], 0.00001);
    CHECK_CLOSE (5, v[1], 0.00001);
    CHECK_CLOSE (4, v[2], 0.00001);
}

TEST (Transpose_post_rotate)
{
    //Quaternion q (30, 0.577350269189626f,0.577350269189626f,0.577350269189626f);
    Quaternion q (90, 0,1,0);
    float a[4];
    q.getAngleAxis (a);

    Transform trs;

    trs.postRotate (a[0], a[1], a[2], a[3]);
    {
        float v[3] = {1,0,0};
        trs.transform (v);
    
        CHECK_CLOSE (0.f, v[0], 0.00001);
        CHECK_CLOSE (0.f, v[1], 0.00001);
        CHECK_CLOSE (-1.f, v[2], 0.00001);
    }

    Quaternion q2 (-90, 0,0,1);
    float b[4];
    q2.getAngleAxis (b);

    trs.postRotate (b[0], b[1], b[2], b[3]);
    {
        float v[3] = {0,1,0};
        trs.transform (v);
    
        CHECK_CLOSE (0.f, v[0], 0.00001);
        CHECK_CLOSE (0.f, v[1], 0.00001);
        CHECK_CLOSE (-1.f, v[2], 0.00001);
    }
 


}


TEST (Transform_transform)
{
    Vector v0 (1,2,3);
    Transform trans;
    trans.postTranslate (5,10,15);
    trans.postScale (2,2,2);

    Vector v1 = trans.transform (v0);

    CHECK_CLOSE (7.f,  v1.x, 0.00001f);
    CHECK_CLOSE (14.f, v1.y, 0.00001f);
    CHECK_CLOSE (21.f, v1.z, 0.00001f);
    CHECK_CLOSE (1.f,  v1.w, 0.00001f);

}

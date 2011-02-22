#include <unittest++/UnitTest++.h>
#include <iostream>
#include <cstring>
#include "m3g/Camera.hpp"
#include "m3g/Group.hpp"
#include "m3g/Transform.hpp"
using namespace std;
using namespace m3g;


TEST (Camera_default_values)
{
    Camera* cam = new Camera;
    Transform trans;
    int type;
    float m[16];

    type = cam->getProjection (&trans);

    // 間違えやすいがデフォルトはジェネリック
    CHECK_EQUAL (Camera::GENERIC, type);

    trans.get (m);
    CHECK_EQUAL (1.f, m[0]);
    CHECK_EQUAL (0.f, m[1]);
    CHECK_EQUAL (0.f, m[2]);
    CHECK_EQUAL (0.f, m[3]);
    CHECK_EQUAL (0.f, m[4]);
    CHECK_EQUAL (1.f, m[5]);
    CHECK_EQUAL (0.f, m[6]);
    CHECK_EQUAL (0.f, m[7]);
    CHECK_EQUAL (0.f, m[8]);
    CHECK_EQUAL (0.f, m[9]);
    CHECK_EQUAL (1.f, m[10]);
    CHECK_EQUAL (0.f, m[11]);
    CHECK_EQUAL (0.f, m[12]);
    CHECK_EQUAL (0.f, m[13]);
    CHECK_EQUAL (0.f, m[14]);
    CHECK_EQUAL (1.f, m[15]);

    delete cam;
}

TEST (Camera_set_variables_parallel)
{
    Camera* cam = new Camera;
    Transform trans;
    float m[16];
    int type;

    float width  = 640;
    float height = 480;
    float aspect_ratio = width/height;
    float fovy   = 1.5;
    float near   = 1;
    float far    = 100;

    cam->setParallel (fovy, aspect_ratio, near, far);

    float params[4];
    type = cam->getProjection (params);
    CHECK_EQUAL (Camera::PARALLEL, type);
    CHECK_CLOSE (fovy        , params[0], 0.00001f);
    CHECK_CLOSE (aspect_ratio, params[1], 0.00001f);
    CHECK_CLOSE (near        , params[2], 0.00001f);
    CHECK_CLOSE (far         , params[3], 0.00001f);
    
    // 仕様上は未定義だが、Desktop-M3Gの実装では正しい値を返す.
    type = cam->getProjection (&trans);
    CHECK_EQUAL (Camera::PARALLEL, type);

    trans.get (m);
    CHECK_CLOSE (1.f       , m[0], 0.00001f);
    CHECK_CLOSE (0.f       , m[1], 0.00001f);
    CHECK_CLOSE (0.f       , m[2], 0.00001f);
    CHECK_CLOSE (0.f       , m[3], 0.00001f);
    CHECK_CLOSE (0.f       , m[4], 0.00001f);
    CHECK_CLOSE (1.33333f  , m[5], 0.00001f);
    CHECK_CLOSE (0.f       , m[6], 0.00001f);
    CHECK_CLOSE (0.f       , m[7], 0.00001f);
    CHECK_CLOSE (0.f       , m[8], 0.00001f);
    CHECK_CLOSE (0.f       , m[9], 0.00001f);
    CHECK_CLOSE (-0.020202f, m[10], 0.00001f);
    CHECK_CLOSE (-1.020200f, m[11], 0.00001f);
    CHECK_CLOSE (0.f       , m[12], 0.00001f);
    CHECK_CLOSE (0.f       , m[13], 0.00001f);
    CHECK_CLOSE (0.f       , m[14], 0.00001f);
    CHECK_CLOSE (1.f       , m[15], 0.00001f);

    delete cam;    
}


TEST (Camera_set_variables_perspective)
{
    Camera*   cam = new Camera;
    Transform trans;
    float     m[16];
    int       type;

    float fovy   = 60;
    float aspect_ratio = 640/480.f;
    float near   = 1;
    float far    = 100;

    cam->setPerspective (fovy, aspect_ratio, near, far);
    
    float params[4];
    type = cam->getProjection (params);
    CHECK_EQUAL (Camera::PERSPECTIVE, type);
    CHECK_CLOSE (fovy        , params[0], 0.00001f);
    CHECK_CLOSE (aspect_ratio, params[1], 0.00001f);
    CHECK_CLOSE (near        , params[2], 0.00001f);
    CHECK_CLOSE (far         , params[3], 0.00001f);

    // 仕様上は未定義だが、Desktop-M3Gの実装では正しい値を返す.
    type = cam->getProjection (&trans);
    CHECK_EQUAL (Camera::PERSPECTIVE, type);

    trans.get (m);
    CHECK_CLOSE (1.29904f , m[0], 0.00001f);
    CHECK_CLOSE (0.f      , m[1], 0.00001f);
    CHECK_CLOSE (0.f      , m[2], 0.00001f);
    CHECK_CLOSE (0.f      , m[3], 0.00001f);
    CHECK_CLOSE (0.f      , m[4], 0.00001f);
    CHECK_CLOSE (1.73205f , m[5], 0.00001f);
    CHECK_CLOSE (0.f      , m[6], 0.00001f);
    CHECK_CLOSE (0.f      , m[7], 0.00001f);
    CHECK_CLOSE (0.f      , m[8], 0.00001f);
    CHECK_CLOSE (0.f      , m[9], 0.00001f);
    CHECK_CLOSE (-1.0202f , m[10], 0.00001f);
    CHECK_CLOSE (-2.0202f , m[11], 0.00001f);
    CHECK_CLOSE (0.f      , m[12], 0.00001f);
    CHECK_CLOSE (0.f      , m[13], 0.00001f);
    CHECK_CLOSE (-1.f     , m[14], 0.00001f);
    CHECK_CLOSE (0.f      , m[15], 0.00001f);

    delete cam;    
}


TEST (Camera_set_variables_generic)
{
    Camera* cam = new Camera;
    int type;

    float m[16] = {1,2,3,4, 5,6,7,8, 9,10,11,12, 13,14,15,16};
    Transform trans;
    trans.set (m);
    cam->setGeneric (&trans);

    type = cam->getProjection (&trans);
    CHECK_EQUAL (Camera::GENERIC, type);

    memset (m, 0, sizeof(0));

    trans.get (m);
    CHECK_CLOSE (1.f, m[0], 0.00001f);
    CHECK_CLOSE (2.f, m[1], 0.00001f);
    CHECK_CLOSE (3.f, m[2], 0.00001f);
    CHECK_CLOSE (4.f, m[3], 0.00001f);
    CHECK_CLOSE (5.f, m[4], 0.00001f);
    CHECK_CLOSE (6.f, m[5], 0.00001f);
    CHECK_CLOSE (7.f, m[6], 0.00001f);
    CHECK_CLOSE (8.f, m[7], 0.00001f);
    CHECK_CLOSE (9.f, m[8], 0.00001f);
    CHECK_CLOSE (10.f, m[9], 0.00001f);
    CHECK_CLOSE (11.f, m[10], 0.00001f);
    CHECK_CLOSE (12.f, m[11], 0.00001f);
    CHECK_CLOSE (13.f, m[12], 0.00001f);
    CHECK_CLOSE (14.f, m[13], 0.00001f);
    CHECK_CLOSE (15.f, m[14], 0.00001f);
    CHECK_CLOSE (16.f, m[15], 0.00001f);
    
    delete cam;    
}



TEST (Camera_duplicate)
{
    Camera* cam0 = new Camera;

    float width  = 640;
    float height = 480;
    float aspect_ratio = width/height;
    float fovy   = 45;
    float near   = 1;
    float far    = 100;
    Group* grp = new Group;
    
    grp->addChild (cam0);
    cam0->setPerspective (fovy, aspect_ratio, near, far);

    Camera* cam1 = cam0->duplicate();

    // duplicate()したNodeのparentはNULL！
    CHECK_EQUAL ((Node*)grp, cam0->getParent());
    CHECK_EQUAL ((Node*)0  , cam1->getParent());

    float params0[4];
    float params1[4];
    CHECK_EQUAL (cam0->getProjection(params0), cam1->getProjection (params1));
    CHECK_EQUAL (params0[0], params1[0]);
    CHECK_EQUAL (params0[1], params1[1]);
    CHECK_EQUAL (params0[2], params1[2]);
    CHECK_EQUAL (params0[3], params1[3]);

    delete cam0;
    delete cam1;
}

TEST (Camera_lookAt)
{
    Camera* cam = new Camera;

    cam->lookAt (1,2,3,
                 -3,-3,-1,
                 3,3,1);

    Transform tra;
    cam->getTransform (&tra);
    
    float m[16];
    tra.get (m);
    
    // 適当に呼び出した時のlookAt関数の値を再度チェックしただけなので
    // 信頼性は低い
    CHECK_CLOSE (m[0],  0.63375f , 0.0001f);
    CHECK_CLOSE (m[1],  0.563612f, 0.0001f);
    CHECK_CLOSE (m[2],  0.529813f, 0.0001f);
    CHECK_CLOSE (m[3],  1.0f     , 0.0001f);
    CHECK_CLOSE (m[4], -0.724286f, 0.0001f);
    CHECK_CLOSE (m[5],  0.191868f, 0.0001f);
    CHECK_CLOSE (m[6],  0.662266f, 0.0001f);
    CHECK_CLOSE (m[7],  2.0f     , 0.0001f);
    CHECK_CLOSE (m[8],  0.271607f, 0.0001f);
    CHECK_CLOSE (m[9], -0.803447f, 0.0001f);
    CHECK_CLOSE (m[10], 0.529813f, 0.0001f);
    CHECK_CLOSE (m[11], 3.0f     , 0.0001f);
    CHECK_CLOSE (m[12], 0.0f     , 0.0001f);
    CHECK_CLOSE (m[13], 0.0f     , 0.0001f);
    CHECK_CLOSE (m[14], 0.0f     , 0.0001f);
    CHECK_CLOSE (m[15], 1.0f     , 0.0001f);

    delete cam;
}

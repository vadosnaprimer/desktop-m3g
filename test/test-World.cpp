#include <unittest++/UnitTest++.h>
#include <iostream>
#include <cstring>
#include "m3g/World.hpp"
#include "m3g/Camera.hpp"
#include "m3g/Background.hpp"
#include "m3g/Light.hpp"
using namespace std;
using namespace m3g;


TEST (World_default_variables)
{
    World* wld = new World;

    CHECK_EQUAL ((Camera*)0    , wld->getActiveCamera());
    CHECK_EQUAL ((Background*)0, wld->getBackground());

    delete wld;
}

TEST (World_set_variables)
{
    Background* bg = new Background;
    Camera* cam    = new Camera;
    World* wld     = new World;

    wld->addChild (cam);
    wld->setActiveCamera (cam);
    wld->setBackground (bg);

    CHECK_EQUAL (cam, wld->getActiveCamera());
    CHECK_EQUAL (bg, wld->getBackground());

    delete bg;
    delete cam;
    delete wld;
}


TEST (World_duplicate)
{
    Background* bg   = new Background;
    Camera*     cam  = new Camera;
    World*      wld0 = new World;

    wld0->addChild (cam);
    wld0->setActiveCamera (cam);
    wld0->setBackground (bg);

    CHECK_EQUAL (1  , wld0->getChildCount());
    CHECK_EQUAL (cam, wld0->getActiveCamera());
    CHECK_EQUAL (bg , wld0->getBackground());

    World* wld1 = wld0->duplicate();

    CHECK_EQUAL (1, wld1->getChildCount());
    CHECK (wld0->getChild(0) != wld1->getChild(0));
    CHECK (cam != wld1->getActiveCamera());
    CHECK (bg  != wld1->getBackground());

    delete bg;
    delete cam;
    delete wld0;
    delete wld1;
}


TEST (World_find)
{
    Background* bg   = new Background;
    Camera*     cam  = new Camera;
    World*      wld  = new World;

    wld->addChild (cam);
    wld->setActiveCamera (cam);
    wld->setBackground (bg);

    bg->setUserID (100);
    cam->setUserID (101);
    wld->setUserID (102);

    CHECK_EQUAL (bg , wld->find(100));
    CHECK_EQUAL (cam, wld->find(101));
    CHECK_EQUAL (wld, wld->find(102));

    delete bg;
    delete cam;
    delete wld;
}

TEST (World_getReferences)
{
    Background* bg  = new Background;
    Camera*     cam = new Camera;
    World*      wld = new World;

    wld->addChild (cam);
    wld->setActiveCamera (cam);
    wld->setBackground (bg);

    int n;
    Object3D* objs[3];
    n = wld->getReferences (objs);
    
    CHECK_EQUAL (3, n);
    CHECK_EQUAL (cam, objs[0]); // 子ノードとして
    CHECK_EQUAL (bg , objs[1]);
    CHECK_EQUAL (cam, objs[2]); // アクティブカメラとして

    delete bg;
    delete cam;
    delete wld;
}


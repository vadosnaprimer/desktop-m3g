#include <unittest++/UnitTest++.h>
#include <iostream>
#include "m3g/Sprite3D.hpp"
#include "m3g/Image2D.hpp"
#include "m3g/Appearance.hpp"
using namespace std;
using namespace m3g;

TEST (Sprite3D_default_variables)
{
    Image2D*    img = new Image2D (Image2D::RGBA, 64, 64);
    Appearance* app = new Appearance;
    Sprite3D*   spr = new Sprite3D (true, img, app);

    CHECK_EQUAL (0, spr->getCropX());
    CHECK_EQUAL (0, spr->getCropY());
    CHECK_EQUAL (64, spr->getCropWidth());
    CHECK_EQUAL (64, spr->getCropHeight());
    CHECK_EQUAL (true, spr->isScaled());
    CHECK_EQUAL (img, spr->getImage());
    CHECK_EQUAL (app, spr->getAppearance());

    delete img;
    delete app;
    delete spr;
}

TEST (Sprite3D_set_variables)
{
    Image2D*     img = new Image2D (Image2D::RGBA, 64, 64);
    Appearance* app = new Appearance;
    Sprite3D*   spr = new Sprite3D (false, img, app);

    spr->setCrop (1,2,30,40);
    CHECK_EQUAL (1, spr->getCropX());
    CHECK_EQUAL (2, spr->getCropY());
    CHECK_EQUAL (30, spr->getCropWidth());
    CHECK_EQUAL (40, spr->getCropHeight());

    Appearance* app2 = new Appearance;
    Image2D*    img2 = new Image2D (Image2D::RGBA, 128, 128);
    spr->setImage (img2);
    spr->setAppearance (app2);

    CHECK_EQUAL (0,    spr->getCropX());
    CHECK_EQUAL (0,    spr->getCropY());
    CHECK_EQUAL (128,  spr->getCropWidth());
    CHECK_EQUAL (128,   spr->getCropHeight());
    CHECK_EQUAL (false, spr->isScaled());
    CHECK_EQUAL (img2, spr->getImage());
    CHECK_EQUAL (app2, spr->getAppearance());

    delete img;
    delete app;
    delete img2;
    delete app2;
    delete spr;
}

TEST (Sprite3D_duplicate)
{
    Image2D*    img  = new Image2D (Image2D::RGBA, 64, 64);
    Appearance* app  = new Appearance;
    Sprite3D*   spr0 = new Sprite3D (false, img, app);

    spr0->setCrop (1,2,30,40);

    Sprite3D* spr1 = spr0->duplicate();

    CHECK_EQUAL (spr0->getCropX()     , spr1->getCropX());
    CHECK_EQUAL (spr0->getCropY()     , spr1->getCropY());
    CHECK_EQUAL (spr0->getCropWidth() , spr1->getCropWidth());
    CHECK_EQUAL (spr0->getCropHeight(), spr1->getCropHeight());
    CHECK_EQUAL (spr0->getImage()     , spr1->getImage());
    CHECK_EQUAL (spr0->getAppearance(), spr1->getAppearance());

    delete img;
    delete app;
    delete spr0;
    delete spr1;
}

TEST (Sprite3D_getReferences)
{
    Image2D*    img = new Image2D (Image2D::RGBA, 64, 64);
    Appearance* app = new Appearance;
    Sprite3D*   spr = new Sprite3D (true, img, app);

    int n;
    Object3D* objs[2];

    n = spr->getReferences (objs);

    CHECK_EQUAL (2, n);
    CHECK_EQUAL (img, objs[0]);
    CHECK_EQUAL (app, objs[1]);

    delete img;
    delete app;
    delete spr;
}

static int count = 0;
static void func (void* p)
{
    count++;
}


TEST (Sprite3D_mark)
{
    Image2D*    img  = new Image2D (Image2D::RGBA, 64, 64);
    Appearance* app  = new Appearance;
    Sprite3D*   spr  = new Sprite3D (false, img, app);

    spr->mark (func);

    CHECK_EQUAL (3, count);

    delete img;
    delete app;
    delete spr;
}

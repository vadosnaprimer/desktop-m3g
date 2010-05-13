#include <unittest++/UnitTest++.h>
#include <iostream>
#include "Sprite3D.hpp"
#include "Image2D.hpp"
#include "Appearance.hpp"
using namespace std;
using namespace m3g;

TEST (Sprite3D_default_variables)
{
    Image2D*    img = new Image2D (Image2D::RGBA, 64, 48);
    Appearance* app = new Appearance;
    Sprite3D*   spr = new Sprite3D (true, img, app);

    CHECK_EQUAL (0, spr->getCropX());
    CHECK_EQUAL (0, spr->getCropY());
    CHECK_EQUAL (64, spr->getCropWidth());
    CHECK_EQUAL (48, spr->getCropHeight());
    CHECK_EQUAL (true, spr->isScaled());
    CHECK_EQUAL (img, spr->getImage());
    CHECK_EQUAL (app, spr->getAppearance());
}

TEST (Sprite3D_set_variables)
{
    Image2D*     img = new Image2D (Image2D::RGBA, 64, 48);
    Appearance* app = new Appearance;
    Sprite3D*   spr = new Sprite3D (false, img, app);

    spr->setCrop (1,2,30,40);
    CHECK_EQUAL (1, spr->getCropX());
    CHECK_EQUAL (2, spr->getCropY());
    CHECK_EQUAL (30, spr->getCropWidth());
    CHECK_EQUAL (40, spr->getCropHeight());

    Appearance* app2 = new Appearance;
    Image2D*    img2 = new Image2D (Image2D::RGBA, 128, 96);
    spr->setImage (img2);
    spr->setAppearance (app2);

    CHECK_EQUAL (0,    spr->getCropX());
    CHECK_EQUAL (0,    spr->getCropY());
    CHECK_EQUAL (128,  spr->getCropWidth());
    CHECK_EQUAL (96,   spr->getCropHeight());
    CHECK_EQUAL (false, spr->isScaled());
    CHECK_EQUAL (img2, spr->getImage());
    CHECK_EQUAL (app2, spr->getAppearance());
}

TEST (Sprite3D_duplicate)
{
    Image2D*     img = new Image2D (Image2D::RGBA, 64, 48);
    Appearance* app = new Appearance;
    Sprite3D*   spr0 = new Sprite3D (false, img, app);

    spr0->setCrop (1,2,30,40);

    Sprite3D* spr1 = spr0->duplicate();

    CHECK_EQUAL (spr0->getCropX()     , spr1->getCropX());
    CHECK_EQUAL (spr0->getCropY()     , spr1->getCropY());
    CHECK_EQUAL (spr0->getCropWidth() , spr1->getCropWidth());
    CHECK_EQUAL (spr0->getCropHeight(), spr1->getCropHeight());
    CHECK_EQUAL (spr0->getImage()     , spr1->getImage());
    CHECK_EQUAL (spr0->getAppearance(), spr1->getAppearance());
}

#include <unittest++/UnitTest++.h>
#include <iostream>
#include "m3g/Background.hpp"
#include "m3g/Image2D.hpp"
using namespace std;
using namespace m3g;


TEST (Background_default_variables)
{
    Background* bg = new Background;

    CHECK_EQUAL (true, bg->isDepthClearEnabled());
    CHECK_EQUAL (true, bg->isColorClearEnabled());
    CHECK_EQUAL (0x00000000, bg->getColor());
    CHECK_EQUAL ((Image2D*)0, bg->getImage());
    CHECK_EQUAL (Background::BORDER, bg->getImageModeX());
    CHECK_EQUAL (Background::BORDER, bg->getImageModeY());

    delete bg;
}

TEST (Background_set_variables)
{
    Background* bg = new Background;
    Image2D* img = new Image2D (Image2D::RGBA, 64, 48);

    bg->setColor (0x12345678);
    bg->setColorClearEnable (false);
    bg->setDepthClearEnable (false);
    bg->setImage (img);
    bg->setImageMode (Background::REPEAT, Background::REPEAT);
    bg->setCrop (1,2,100,200);

    CHECK_EQUAL (false, bg->isDepthClearEnabled());
    CHECK_EQUAL (false, bg->isColorClearEnabled());
    CHECK_EQUAL (0x12345678, bg->getColor());
    CHECK_EQUAL (img, bg->getImage());
    CHECK_EQUAL (Background::REPEAT, bg->getImageModeX());
    CHECK_EQUAL (Background::REPEAT, bg->getImageModeY());
    CHECK_EQUAL (1, bg->getCropX());
    CHECK_EQUAL (2, bg->getCropY());
    CHECK_EQUAL (100, bg->getCropWidth());
    CHECK_EQUAL (200, bg->getCropHeight());

    delete img;
    delete bg;
}

TEST (Background_duplicate)
{
    Background* bg0 = new Background;
    Image2D*    img = new Image2D (Image2D::RGBA, 64, 48);

    bg0->setColor (0x12345678);
    bg0->setColorClearEnable (false);
    bg0->setDepthClearEnable (false);
    bg0->setImage (img);
    bg0->setImageMode (Background::REPEAT, Background::REPEAT);
    bg0->setCrop (1,2,100,200);

    Background* bg1 = bg0->duplicate();

    CHECK_EQUAL (bg0->isDepthClearEnabled(), bg1->isDepthClearEnabled());
    CHECK_EQUAL (bg0->isColorClearEnabled(), bg1->isColorClearEnabled());
    CHECK_EQUAL (bg0->getColor()           , bg1->getColor());
    CHECK_EQUAL (bg0->getImage()           , bg1->getImage());
    CHECK_EQUAL (bg0->getImageModeX()      , bg1->getImageModeX());
    CHECK_EQUAL (bg0->getImageModeY()      , bg1->getImageModeY());
    CHECK_EQUAL (bg0->getCropX()           , bg1->getCropX());
    CHECK_EQUAL (bg0->getCropY()           , bg1->getCropY());
    CHECK_EQUAL (bg0->getCropWidth()       , bg1->getCropWidth());
    CHECK_EQUAL (bg0->getCropHeight()      , bg1->getCropHeight());

    delete img;
    delete bg0;
    delete bg1;
}

TEST (Background_find)
{
    Background* bg  = new Background;
    Image2D*    img = new Image2D (Image2D::RGBA, 64, 48);
    bg->setImage (img);

    bg->setUserID (100);
    img->setUserID (101);

    CHECK_EQUAL (bg, bg->find (100));
    CHECK_EQUAL (img, bg->find (101));

    delete img;
    delete bg;
}

TEST (Background_getReferences)
{
    Background* bg  = new Background;
    Image2D*    img = new Image2D (Image2D::RGBA, 64, 48);
    bg->setImage (img);

    int n;
    Object3D* objs[1];

    n = bg->getReferences (objs);

    CHECK_EQUAL (1, n);
    CHECK_EQUAL (img, objs[0]);

    delete img;
    delete bg;
}

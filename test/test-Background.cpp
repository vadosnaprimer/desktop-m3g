#include <unittest++/UnitTest++.h>
#include <iostream>
#include "Background.hpp"
#include "Image2D.hpp"
using namespace std;
using namespace m3g;


TEST (Background_default_variables)
{
  Background* bg = new Background;

  CHECK_EQUAL (OBJTYPE_BACKGROUND, bg->getObjectType());
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

#include <unittest++/UnitTest++.h>
#include <iostream>
#include "Fog.hpp"
using namespace std;
using namespace m3g;


TEST (Fog_default_variables)
{
  Fog* fog = new Fog;

  CHECK_EQUAL (OBJTYPE_FOG, fog->getObjectType());
  CHECK_EQUAL (Fog::LINEAR, fog->getMode());
  CHECK_EQUAL (1, fog->getDensity());
  CHECK_EQUAL (0, fog->getNearDistance());
  CHECK_EQUAL (1, fog->getFarDistance());
  CHECK_EQUAL (0, fog->getColor());

  delete fog;
}

TEST (Fog_set_variables)
{
  Fog* fog = new Fog;
  
  fog->setMode (Fog::EXPONENTIAL);
  fog->setColor (0x12345678);
  fog->setDensity (100);
  fog->setLinear (1,10);

  CHECK_EQUAL (Fog::EXPONENTIAL, fog->getMode());
  CHECK_EQUAL (100, fog->getDensity());
  CHECK_EQUAL (1, fog->getNearDistance());
  CHECK_EQUAL (10, fog->getFarDistance());
  CHECK_EQUAL (0x00345678, fog->getColor());

  delete fog;
}

TEST (Fog_Object3D)
{
  Fog* fog = new Fog;
  fog->setUserID (100);
  CHECK_EQUAL (100, fog->getUserID());
}

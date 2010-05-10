#include <unittest++/UnitTest++.h>
#include <iostream>
#include <cstring>
#include "Light.hpp"
using namespace std;
using namespace m3g;

TEST (Light_default_variables)
{
  Light* lig = new Light;

  CHECK_EQUAL (Light::DIRECTIONAL, lig->getMode());
  CHECK_EQUAL (0x00ffffff, lig->getColor());
  CHECK_EQUAL (1.f, lig->getConstantAttenuation());
  CHECK_EQUAL (0.f, lig->getLinearAttenuation());
  CHECK_EQUAL (0.f, lig->getQuadraticAttenuation());
  CHECK_EQUAL (45.f, lig->getSpotAngle());
  CHECK_EQUAL (0.f, lig->getSpotExponent());

  delete lig;
}

TEST (Light_set_variables)
{
  Light* lig = new Light;

  lig->setAttenuation (1,2,3);
  lig->setColor (0x12345678);
  lig->setIntensity (100);
  lig->setMode (Light::OMNI);
  lig->setSpotAngle (90);
  lig->setSpotExponent (2);

  CHECK_EQUAL (Light::OMNI, lig->getMode());
  CHECK_EQUAL (0x00345678,  lig->getColor());
  CHECK_EQUAL (1.f , lig->getConstantAttenuation());
  CHECK_EQUAL (2.f,  lig->getLinearAttenuation());
  CHECK_EQUAL (3.f,  lig->getQuadraticAttenuation());
  CHECK_EQUAL (90.f, lig->getSpotAngle());
  CHECK_EQUAL (2.f,  lig->getSpotExponent());

  delete lig;
}


TEST (Light_duplicate)
{
  Light* lig0 = new Light;

  lig0->setAttenuation (1,2,3);
  lig0->setColor (0x12345678);
  lig0->setIntensity (100);
  lig0->setMode (Light::OMNI);
  lig0->setSpotAngle (90);
  lig0->setSpotExponent (2);

  Light* lig1 = lig0->duplicate();

  CHECK_EQUAL (lig0->getMode()                , lig1->getMode());
  CHECK_EQUAL (lig0->getColor()               , lig1->getColor());
  CHECK_EQUAL (lig0->getConstantAttenuation() , lig1->getConstantAttenuation());
  CHECK_EQUAL (lig0->getLinearAttenuation()   , lig1->getLinearAttenuation());
  CHECK_EQUAL (lig0->getQuadraticAttenuation(), lig1->getQuadraticAttenuation());
  CHECK_EQUAL (lig0->getSpotAngle()           , lig1->getSpotAngle());
  CHECK_EQUAL (lig0->getSpotExponent()        , lig1->getSpotExponent());

  delete lig0;
  delete lig1;
}

#include <unittest++/UnitTest++.h>
#include <iostream>
#include <cstring>
#include "Light.hpp"
using namespace std;
using namespace m3g;

TEST (Light_default_variables)
{
  Light* lig = new Light;

  CHECK_EQUAL (OBJTYPE_LIGHT, lig->getObjectType());
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

TEST (Light_findByObjectType)
{
  Light* lig = new Light;

  vector<Object3D*> objs;

  lig->findByObjectType (OBJTYPE_LIGHT, objs);

  CHECK_EQUAL (1, objs.size());
  CHECK_EQUAL (lig, dynamic_cast<Light*>(objs[0]));

  delete lig;
}


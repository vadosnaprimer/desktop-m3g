#include <unittest++/UnitTest++.h>
#include <iostream>
#include "CompositingMode.hpp"
using namespace std;
using namespace m3g;


TEST (CompositingMode_default_variables)
{
  CompositingMode* cmode = new CompositingMode;
  
  CHECK_EQUAL (OBJTYPE_COMPOSITING_MODE, cmode->getObjectType());
  CHECK_EQUAL (CompositingMode::REPLACE, cmode->getBlending());
  CHECK_EQUAL (0.0, cmode->getAlphaThreshold());
  CHECK_EQUAL (0.0, cmode->getDepthOffsetFactor());
  CHECK_EQUAL (0.0, cmode->getDepthOffsetUnits());
  CHECK_EQUAL (true, cmode->isDepthTestEnabled());
  CHECK_EQUAL (true, cmode->isDepthWriteEnabled());
  CHECK_EQUAL (true, cmode->isColorWriteEnabled());
  CHECK_EQUAL (true, cmode->isAlphaWriteEnabled());

  delete cmode;
}

TEST (CompositingMode_set_variables)
{
  CompositingMode* cmode = new CompositingMode;
  
  cmode->setBlending (CompositingMode::MODULATE);
  cmode->setAlphaThreshold (1.0);
  cmode->setDepthOffset (1.0, 2.0);
  cmode->setDepthTestEnable (false);
  cmode->setDepthWriteEnable (false);
  cmode->setAlphaWriteEnable (false);
  cmode->setColorWriteEnable (false);


  CHECK_EQUAL (CompositingMode::MODULATE, cmode->getBlending());
  CHECK_EQUAL (1.0, cmode->getAlphaThreshold());
  CHECK_EQUAL (1.0, cmode->getDepthOffsetFactor());
  CHECK_EQUAL (2.0, cmode->getDepthOffsetUnits());
  CHECK_EQUAL (false, cmode->isDepthTestEnabled());
  CHECK_EQUAL (false, cmode->isDepthWriteEnabled());
  CHECK_EQUAL (false, cmode->isColorWriteEnabled());
  CHECK_EQUAL (false, cmode->isAlphaWriteEnabled());

  delete cmode;
}



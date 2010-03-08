#include <unittest++/UnitTest++.h>
#include <iostream>
#include "PolygonMode.hpp"
using namespace std;
using namespace m3g;


TEST (PolygonMode_default_variables)
{
  PolygonMode* pmode = new PolygonMode;

  CHECK_EQUAL (OBJTYPE_POLYGON_MODE, pmode->getObjectType());
  CHECK_EQUAL (PolygonMode::CULL_BACK, pmode->getCulling());
  CHECK_EQUAL (PolygonMode::WINDING_CCW, pmode->getWinding());
  CHECK_EQUAL (PolygonMode::SHADE_SMOOTH, pmode->getShading());
  CHECK_EQUAL (false, pmode->isLocalCameraLightingEnabled());
  CHECK_EQUAL (false, pmode->isPerspectiveCorrectionEnabled());
  CHECK_EQUAL (false, pmode->isTwoSidedLightingEnabled());
  
  delete pmode;
}


TEST (PolygonMode_set_variables)
{
  PolygonMode* pmode = new PolygonMode;
  
  pmode->setCulling (PolygonMode::CULL_NONE);
  pmode->setWinding (PolygonMode::WINDING_CW);
  pmode->setShading (PolygonMode::SHADE_FLAT);
  pmode->setLocalCameraLightingEnable (true);
  pmode->setPerspectiveCorrectionEnable (true);
  pmode->setTwoSidedLightingEnable (true);
}


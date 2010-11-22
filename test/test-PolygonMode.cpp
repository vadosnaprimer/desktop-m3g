#include <unittest++/UnitTest++.h>
#include <iostream>
#include "m3g/PolygonMode.hpp"
using namespace std;
using namespace m3g;


TEST (PolygonMode_default_variables)
{
    PolygonMode* pmode = new PolygonMode;

    CHECK_EQUAL (PolygonMode::CULL_BACK, pmode->getCulling());
    CHECK_EQUAL (PolygonMode::WINDING_CCW, pmode->getWinding());
    CHECK_EQUAL (PolygonMode::SHADE_SMOOTH, pmode->getShading());
    CHECK_EQUAL (false, pmode->isTwoSidedLightingEnabled());
    CHECK_EQUAL (true, pmode->isLocalCameraLightingEnabled());
    CHECK_EQUAL (true, pmode->isPerspectiveCorrectionEnabled());
  
    delete pmode;
}


TEST (PolygonMode_set_variables)
{
    PolygonMode* pmode = new PolygonMode;
  
    pmode->setCulling (PolygonMode::CULL_NONE);
    pmode->setWinding (PolygonMode::WINDING_CW);
    pmode->setShading (PolygonMode::SHADE_FLAT);
    pmode->setTwoSidedLightingEnable (true);
    pmode->setLocalCameraLightingEnable (false);
    pmode->setPerspectiveCorrectionEnable (false);

    CHECK_EQUAL (PolygonMode::CULL_NONE, pmode->getCulling());
    CHECK_EQUAL (PolygonMode::WINDING_CW, pmode->getWinding());
    CHECK_EQUAL (PolygonMode::SHADE_FLAT, pmode->getShading());
    CHECK_EQUAL (true,  pmode->isTwoSidedLightingEnabled());
    CHECK_EQUAL (false, pmode->isLocalCameraLightingEnabled());
    CHECK_EQUAL (false, pmode->isPerspectiveCorrectionEnabled());
  
    delete pmode;
}

TEST (PolygonMode_duplicate)
{
    PolygonMode* pmode0 = new PolygonMode;
  
    pmode0->setCulling (PolygonMode::CULL_NONE);
    pmode0->setWinding (PolygonMode::WINDING_CW);
    pmode0->setShading (PolygonMode::SHADE_FLAT);
    pmode0->setTwoSidedLightingEnable (true);
    pmode0->setLocalCameraLightingEnable (false);
    pmode0->setPerspectiveCorrectionEnable (false);

    PolygonMode* pmode1 = pmode0->duplicate();

    CHECK_EQUAL (pmode0->getCulling()                    , pmode1->getCulling());
    CHECK_EQUAL (pmode0->getWinding()                    , pmode1->getWinding() );
    CHECK_EQUAL (pmode0->getShading()                    , pmode1->getShading());
    CHECK_EQUAL (pmode0->isTwoSidedLightingEnabled()     , pmode1->isTwoSidedLightingEnabled());
    CHECK_EQUAL (pmode0->isLocalCameraLightingEnabled()  , pmode1->isLocalCameraLightingEnabled());
    CHECK_EQUAL (pmode0->isPerspectiveCorrectionEnabled(), pmode1->isPerspectiveCorrectionEnabled());
  
    delete pmode0;
    delete pmode1;
}


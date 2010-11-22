#include <unittest++/UnitTest++.h>
#include <iostream>
#include "m3g/CompositingMode.hpp"
using namespace std;
using namespace m3g;


TEST (CompositingMode_default_variables)
{
    CompositingMode* cmode = new CompositingMode;
  
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

TEST (CompositingMode_duplicate)
{
    CompositingMode* cmode0 = new CompositingMode;
  
    cmode0->setBlending (CompositingMode::MODULATE);
    cmode0->setAlphaThreshold (1.0);
    cmode0->setDepthOffset (1.0, 2.0);
    cmode0->setDepthTestEnable (false);
    cmode0->setDepthWriteEnable (false);
    cmode0->setAlphaWriteEnable (false);
    cmode0->setColorWriteEnable (false);

    CompositingMode* cmode1 = cmode0->duplicate();

    CHECK_EQUAL (cmode0->getBlending()         , cmode1->getBlending());
    CHECK_EQUAL (cmode0->getAlphaThreshold()   , cmode1->getAlphaThreshold());
    CHECK_EQUAL (cmode0->getDepthOffsetFactor(), cmode1->getDepthOffsetFactor());
    CHECK_EQUAL (cmode0->getDepthOffsetUnits() , cmode1->getDepthOffsetUnits());
    CHECK_EQUAL (cmode0->isDepthTestEnabled()  , cmode1->isDepthTestEnabled());
    CHECK_EQUAL (cmode0->isDepthWriteEnabled() , cmode1->isDepthWriteEnabled());
    CHECK_EQUAL (cmode0->isColorWriteEnabled() , cmode1->isColorWriteEnabled());
    CHECK_EQUAL (cmode0->isAlphaWriteEnabled() , cmode1->isAlphaWriteEnabled());

    delete cmode0;
    delete cmode1;
}



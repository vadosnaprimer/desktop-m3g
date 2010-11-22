#include <unittest++/UnitTest++.h>
#include <iostream>
#include "m3g/AnimationTrack.hpp"
#include "m3g/AnimationController.hpp"
#include "m3g/KeyframeSequence.hpp"
using namespace std;
using namespace m3g;


TEST (AnimationController_default_variables)
{
    AnimationController* controller = new AnimationController;

    CHECK_EQUAL (0, controller->getActiveIntervalStart());
    CHECK_EQUAL (0, controller->getActiveIntervalEnd());
    CHECK_EQUAL (0, controller->getRefWorldTime());
    CHECK_EQUAL (1, controller->getSpeed());
    CHECK_EQUAL (1, controller->getWeight());
    CHECK_EQUAL (true, controller->isActive(-1000));
}



TEST (AnimationController_set_variables)
{
    AnimationController* controller = new AnimationController;
    controller->setActiveInterval (1000, 5000);
    controller->setPosition (10, 2000);
    controller->setWeight (0.5);
    controller->setSpeed (1, 2000);

    CHECK_EQUAL (true,  controller->isActive(1000));
    CHECK_EQUAL (false, controller->isActive(5000));
    CHECK_EQUAL (1000,  controller->getActiveIntervalStart());
    CHECK_EQUAL (5000,  controller->getActiveIntervalEnd());
    CHECK_EQUAL (2000,  controller->getRefWorldTime());
    CHECK_EQUAL (1,     controller->getSpeed());
    CHECK_EQUAL (0.5,   controller->getWeight());

    CHECK_EQUAL (10, controller->getPosition(2000));
    CHECK_EQUAL (20, controller->getPosition(2010));

    controller->setSpeed (2,2000);

    CHECK_EQUAL (10, controller->getPosition(2000));
    CHECK_EQUAL (30, controller->getPosition(2010));

    controller->setSpeed (4,2010);

    CHECK_EQUAL (30, controller->getPosition(2010));
    CHECK_EQUAL (70, controller->getPosition(2020));

    controller->setWeight (0);
    CHECK_EQUAL (false, controller->isActive(1000));
}

TEST (AnimationController_duplicate)
{
    AnimationController* ctr0 = new AnimationController;
    ctr0->setActiveInterval (1000, 5000);
    ctr0->setPosition (10, 2000);
    ctr0->setWeight (0.5);
    ctr0->setSpeed (1, 2000);

    AnimationController* ctr1 = ctr0->duplicate();
    CHECK_EQUAL (ctr0->getActiveIntervalStart(), ctr1->getActiveIntervalStart());
    CHECK_EQUAL (ctr0->getActiveIntervalEnd(), ctr1->getActiveIntervalEnd());
    CHECK_EQUAL (ctr0->getPosition(100), ctr1->getPosition(100));
    CHECK_EQUAL (ctr0->getRefWorldTime(), ctr1->getRefWorldTime());
    CHECK_EQUAL (ctr0->getSpeed(), ctr1->getSpeed());
    CHECK_EQUAL (ctr0->getWeight(), ctr1->getWeight());
}




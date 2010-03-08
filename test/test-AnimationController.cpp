#include <unittest++/UnitTest++.h>
#include <iostream>
#include "AnimationTrack.hpp"
#include "AnimationController.hpp"
#include "KeyframeSequence.hpp"
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
  CHECK_EQUAL (true, controller->isActiveInterval(-1000));
}



TEST (AnimationController_set_variables)
{
  AnimationController* controller = new AnimationController;
  controller->setActiveInterval (1000, 5000);
  controller->setPosition (10, 2000);
  controller->setWeight (0.5);
  controller->setSpeed (1, 2000);

  CHECK_EQUAL (true, controller->isActiveInterval(1000));
  CHECK_EQUAL (false, controller->isActiveInterval(5000));
  CHECK_EQUAL (1000, controller->getActiveIntervalStart());
  CHECK_EQUAL (5000, controller->getActiveIntervalEnd());
  CHECK_EQUAL (2000, controller->getRefWorldTime());
  CHECK_EQUAL (1,    controller->getSpeed());
  CHECK_EQUAL (0.5,  controller->getWeight());

  CHECK_EQUAL (10, controller->getPosition(2000));
  CHECK_EQUAL (20, controller->getPosition(2010));

  controller->setSpeed (2,2000);

  CHECK_EQUAL (10, controller->getPosition(2000));
  CHECK_EQUAL (30, controller->getPosition(2010));

  controller->setSpeed (4,2010);

  CHECK_EQUAL (30, controller->getPosition(2010));
  CHECK_EQUAL (70, controller->getPosition(2020));
}





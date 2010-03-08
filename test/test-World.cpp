#include <unittest++/UnitTest++.h>
#include <iostream>
#include <cstring>
#include "World.hpp"
#include "Camera.hpp"
#include "Background.hpp"
#include "Light.hpp"
using namespace std;
using namespace m3g;


TEST (World_default_variables)
{
  World* wld = new World;

  CHECK_EQUAL (OBJTYPE_WORLD, wld->getObjectType());
  CHECK_EQUAL ((Camera*)0, wld->getActiveCamera());
  CHECK_EQUAL ((Background*)0, wld->getBackground());

  delete wld;
}

TEST (World_set_variables)
{
  Background* bg = new Background;
  Camera* cam    = new Camera;
  World* wld     = new World;

  wld->addChild (cam);
  wld->setActiveCamera (cam);
  wld->setBackground (bg);

  CHECK_EQUAL (cam, wld->getActiveCamera());
  CHECK_EQUAL (bg, wld->getBackground());

  delete bg;
  delete cam;
  delete wld;
}



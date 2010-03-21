#include "World.hpp"
#include "Camera.hpp"
#include "Background.hpp"
#include "Light.hpp"
#include <iostream>
#include <cmath>
#include "Exception.hpp"
using namespace m3g;
using namespace std;


World:: World () :
  background(0), camera(0)
{
  setObjectType (OBJTYPE_WORLD);
}

World:: ~World ()
{
}

int World:: animate (int world_time)
{
  //cout << "World: animate, time=" << world_time << "\n";

  Group:: animate (world_time);

  if (background) {
    background->animate (world_time);
  }
  if (camera) {
    camera->animate (world_time);
  }

  return 0;
}

Camera* World:: getActiveCamera () const
{
    return camera;
}

Background* World:: getBackground () const
{
    return background;
}

void World:: setActiveCamera (Camera* cam)
{
  if (cam == NULL) {
    throw NullPointException (__FILE__, __func__, "Camera is NULL.");
  }

  vector<Object3D*> objs;
  for (int i = 0; i < getChildCount(); i++) {
    Node* node = getChild(i);
    node->findByObjectType (OBJTYPE_CAMERA, objs);
  }
  Camera* c = 0;
  for (int i = 0; i < (int)objs.size(); i++) {
    if (cam == dynamic_cast<Camera*>(objs[i])) {
      c = cam;
    }
  }
  if (c == 0) {
    throw IllegalArgumentException (__FILE__, __func__, "Can't find such camera in World.");
  }

  camera = c;
}

void World:: setBackground (Background* bg)
{
  if (bg == NULL) {
    throw NullPointException (__FILE__, __func__, "Background is NULL.");
  }

  background = bg;
}

/**
 * Note: World should be rendered via all rendering pass.
 *   pass=0: render background and camera.
 *   pass=1: render lights.
 *   pass=2: render objets.
 */
void World:: render (int pass, int index) const
{
  //cout << "World render\n";

  switch (pass) {
  case 0: {
    if (background) {
      background->render (0, index);
    }
    else {
      glClearColor (0,0,0,0);   // r,g,b,a
      glClearDepth (1.0f);
      glClear      (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    Camera* cam = getActiveCamera();
    cam->render (0, index);
    break;
  }
  case 1:
    Light::resetGLIndex ();
    // fall through
  case 2:
  default: {
    Group::render (pass, index);
  }
  }

}



std::ostream& World::print (std::ostream& out) const
{
  out << "World: \n";
  if (camera)
    out << "  active camera = " << *camera;
  else 
    out << "  active camera = 0\n";
  if (background)
    out << "  background = " << *background;
  else 
    out << "  background = 0\n";
  Group::print (out);
  return out;
}

std::ostream& operator<< (std::ostream& out, const m3g::World& wld)
{
  return wld.print(out);
}

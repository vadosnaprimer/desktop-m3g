#include "World.hpp"
#include "Camera.hpp"
#include "Background.hpp"
#include "Light.hpp"
#include <iostream>
#include <cmath>
#include "Exception.hpp"
#include "RenderState.hpp"
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

World* World:: duplicate () const
{
  World* wld   = new World (*this);
  Group* grp   = Group::duplicate ();
  *(Group*)wld = *grp;
  delete grp;

  wld->background = this->background->duplicate();
  for (int i = 0; i < getChildCount(); i++) {
    if (getChild(i) == camera) {
      wld->setActiveCamera (dynamic_cast<Camera*>(wld->getChild(i)));
      break;
    }
  }
  return wld;
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

  // TODO: 今ひとつ
  // あとで修正する。
  // カメラは問答無用でセットして良い。
  // rendering()の時には子ノードとして存在していなければならない

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
void World:: render (RenderState& state) const
{
  if (camera == NULL) {
    throw IllegalStateException (__FILE__, __func__, "Active camera is NULL.");
  }
  
  //cout << "World render\n";

  switch (state.pass) {
  case 0: {
    if (background) {
      background->render (state);
    }
    else {
      glClearColor (0,0,0,0);   // r,g,b,a
      glClearDepth (1.0f);
      glClear      (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    camera->render (state);
    break;
  }
  case 1:
    state.light_index = 0;
    Group::render (state);
    break;
  case 2:
    Group::render (state);
    break;
  default:
    throw IllegalStateException (__FILE__, __func__, "Render pass is invalid, pass=%d.", state.pass);
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

  //Group::print (out);
  for (int i = 0; i < (int)children.size(); i++) {
    out << "  [" << i << "] : ";
    children[i]->print(out);
  }
  return out;
}

std::ostream& operator<< (std::ostream& out, const m3g::World& wld)
{
  return wld.print(out);
}

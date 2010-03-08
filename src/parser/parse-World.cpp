#include <strstream>
#include <iostream>
#include "../World.hpp"
#include "../Group.hpp"
#include "../Camera.hpp"
#include "../Background.hpp"
#include "parse-Group.hpp"

using namespace std;
using namespace m3g;

void parse_World (istrstream& iss, vector<Object3D*>& objs)
{
  World* wld = new World;

  parse_Group (iss, objs, wld);

  unsigned int active_camera_index;
  iss.read ((char*)&active_camera_index, 4);
  if (active_camera_index > 0) {
    Camera* cam = dynamic_cast<Camera*>(objs.at(active_camera_index));
    wld->setActiveCamera (cam);
  }

  unsigned int background_index;
  iss.read ((char*)&background_index, 4);
  if (background_index > 0) {
    Background* bg = dynamic_cast<Background*>(objs.at(background_index));
    wld->setBackground (bg);
  }

  /*
  wld->print (cout);
  wld->Group::print (cout);
  wld->Node::print (cout);
  wld->Transformable::print (cout);
  wld->Object3D::print (cout);
  */

  objs.push_back (wld);
}

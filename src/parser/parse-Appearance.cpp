#include <strstream>
#include <iostream>
#include "../AnimationTrack.hpp"
#include "../Appearance.hpp"
#include "../Fog.hpp"
#include "../KeyframeSequence.hpp"
#include "../AnimationController.hpp"
#include "../CompositingMode.hpp"
#include "../PolygonMode.hpp"
#include "../Texture2D.hpp"
#include "../Material.hpp"
#include "parse-Object3D.hpp"
using namespace std;
using namespace m3g;


void parse_Appearance (istrstream& iss, vector<Object3D*>& objs)
{
  Appearance* app = new Appearance;

  parse_Object3D (iss, objs, app);
  
  unsigned char layer;
  iss.read ((char*)&layer, 1);
  app->setLayer (layer);

  int compositing_mode_index;
  iss.read ((char*)&compositing_mode_index, 4);
  if (compositing_mode_index > 0) {
    CompositingMode* cmode = dynamic_cast<CompositingMode*>(objs.at(compositing_mode_index));
    app->setCompositingMode (cmode);
  }

  int fog_index;
  iss.read ((char*)&fog_index, 4);
  if (fog_index > 0) {
    Fog* fog = dynamic_cast<Fog*>(objs.at(fog_index));
    app->setFog (fog);
  }

  unsigned int polygon_mode_index;
  iss.read ((char*)&polygon_mode_index, 4);
  if (polygon_mode_index > 0) {
    PolygonMode * pmode = dynamic_cast<PolygonMode*>(objs.at(polygon_mode_index));
    app->setPolygonMode (pmode);
  }

  unsigned int material_index;
  iss.read ((char*)&material_index, 4);
  if (material_index > 0) {
    Material* mat = dynamic_cast<Material*>(objs.at(material_index));
    app->setMaterial (mat);
  }

  unsigned int textures_count;
  iss.read ((char*)&textures_count, 4);
  for (int i = 0; i < (int)textures_count; i++) {
    unsigned int textures_index;
    iss.read ((char*)&textures_index, 4);
    Texture2D* tex = dynamic_cast<Texture2D*>(objs.at(textures_index));
    app->setTexture (i, tex);
  }
 
  /* 
  app->print (cout);
  app->Object3D::print (cout);
  */

  objs.push_back (app);
}

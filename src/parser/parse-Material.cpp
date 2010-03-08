#include <strstream>
#include <iostream>
#include "../Material.hpp"
#include "parse-Object3D.hpp"
using namespace std;
using namespace m3g;

void parse_Material (istrstream& iss, vector<Object3D*>& objs)
{
  Material* mat = new Material;

  parse_Object3D (iss, objs, mat);

  unsigned int ambient_color  = 0;
  iss.read ((char*)&ambient_color, 3);
  mat->setColor (Material::AMBIENT, ambient_color);

  // 多分間違えている
  unsigned char a,r,g,b;
  iss.read ((char*)&r, 1);
  iss.read ((char*)&g, 1);
  iss.read ((char*)&b, 1);
  iss.read ((char*)&a, 1);
  unsigned int diffuse_color = (a<<24)|(r<<16)|(g<<8)|(b<<0);
  mat->setColor (Material::DIFFUSE, diffuse_color);

  unsigned int emissive_color = 0;
  iss.read ((char*)&emissive_color, 3);
  mat->setColor (Material::EMISSIVE, emissive_color);

  unsigned int specular_color = 0;
  iss.read ((char*)&specular_color, 3);
  mat->setColor (Material::SPECULAR, specular_color);

  float shiness;
  iss.read ((char*)&shiness, 4);
  mat->setShininess (shiness);

  bool vertex_color_tracking_enabled;
  iss.read ((char*)&vertex_color_tracking_enabled, 1);
  mat->setVertexColorTrackingEnable (vertex_color_tracking_enabled);

  /*
  mat->print (cout);
  mat->Object3D::print (cout);
  */

  objs.push_back (mat);
}

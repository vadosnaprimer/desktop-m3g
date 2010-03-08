#include <strstream>
#include <iostream>
#include <vector>
#include "../Fog.hpp"
using namespace std;
using namespace m3g;

void parse_Fog (istrstream& iss, vector<Object3D*>& objs)
{
  int color = 0;
  unsigned char mode;
  float density;
  float near;
  float far;

  Fog* fog = new Fog;

  iss.read ((char*)&color, 3);
  iss.read ((char*)&mode, 1);
  fog->setColor (color);
  fog->setMode (mode);

  if (mode == Fog::EXPONENTIAL) {
    iss.read ((char*)&density, 4);
    fog->setDensity (density);

  } else if (mode == Fog::LINEAR) {
    iss.read ((char*)&near, 4);
    iss.read ((char*)&far, 4);
    fog->setLinear (near, far);
  }

  objs.push_back (fog);
}


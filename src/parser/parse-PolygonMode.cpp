#include <strstream>
#include <iostream>
#include "../PolygonMode.hpp"
#include "parse-Object3D.hpp"
using namespace std;
using namespace m3g;

void parse_PolygonMode (istrstream& iss, vector<Object3D*>& objs)
{
  PolygonMode* pmode = new PolygonMode;

  parse_Object3D (iss, objs, pmode);

  unsigned char culling;
  iss.read ((char*)&culling, 1);
  pmode->setCulling (culling);

  unsigned char shading;
  iss.read ((char*)&shading, 1);
  pmode->setShading (shading);

  unsigned char winding;
  iss.read ((char*)&winding, 1);
  pmode->setWinding (winding);

  bool two_sided_lighting_enabled;
  iss.read ((char*)&two_sided_lighting_enabled, 1);
  pmode->setTwoSidedLightingEnable (two_sided_lighting_enabled);

  bool local_camera_lighting_enabled;
  iss.read ((char*)&local_camera_lighting_enabled, 1);
  pmode->setLocalCameraLightingEnable (local_camera_lighting_enabled);

  bool perspective_correction_enabled;
  iss.read ((char*)&perspective_correction_enabled, 1);
  pmode->setPerspectiveCorrectionEnable (perspective_correction_enabled);

  objs.push_back (pmode);
}

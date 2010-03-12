#include "PolygonMode.hpp"
#include "m3gexcept.hpp"
#include <iostream>
using namespace std;
using namespace m3g;


PolygonMode:: PolygonMode () :
  culling(CULL_BACK), winding(WINDING_CCW) ,shading(SHADE_SMOOTH),
  two_sided_lighting(false), local_camera_lighting(false), perspective_correction(false)
{
  setObjectType (OBJTYPE_POLYGON_MODE);
}

PolygonMode:: ~PolygonMode ()
{
}

int PolygonMode:: getCulling () const
{
    return culling;
}

int PolygonMode:: getShading () const
{
    return shading;
}

int PolygonMode:: getWinding () const
{
    return winding;
}

bool PolygonMode:: isLocalCameraLightingEnabled () const
{
    return local_camera_lighting;
}

bool PolygonMode:: isPerspectiveCorrectionEnabled () const
{
    return perspective_correction;
}

bool PolygonMode:: isTwoSidedLightingEnabled () const
{
    return two_sided_lighting;
}

void PolygonMode:: setCulling (int mode)
{
  if (mode != CULL_BACK && mode != CULL_FRONT && mode != CULL_NONE) {
    throw invalid_argument ("Illegal culling mode is specified.\n");
  }
  culling = mode;
}

void PolygonMode:: setLocalCameraLightingEnable (bool enable)
{
  local_camera_lighting = enable;
}

void PolygonMode:: setPerspectiveCorrectionEnable (bool enable)
{
  perspective_correction = enable;
}

void PolygonMode:: setShading (int mode)
{
  if (mode != SHADE_FLAT && mode != SHADE_SMOOTH) {
    throw invalid_argument ("Illegal shading mode is specified.\n");
  }
  shading = mode;
}

void PolygonMode:: setTwoSidedLightingEnable (bool enable)
{
  two_sided_lighting = enable;
}

void PolygonMode:: setWinding (int mode)
{
  if (mode != WINDING_CCW && mode != WINDING_CW) {
    throw invalid_argument ("Illegal winding mode is specified.\n");
  }
  winding = mode;
}

void PolygonMode:: render (int pass, int index) const
{
  if (pass != 2) {
    return;
  }

  Object3D:: render (pass, index);
}

std::ostream& PolygonMode:: print (std::ostream& out) const
{
  return out;
}

std::ostream& operator<< (std::ostream& out, const PolygonMode& pm)
{
    return out;
}


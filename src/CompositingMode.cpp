#include <iostream>
#include "CompositingMode.hpp"
#include "Exception.hpp"
using namespace m3g;
using namespace std;


CompositingMode:: CompositingMode () :
  blending_mode(REPLACE), alpha_threshold(0), depth_offset(0,0),
  depth_test(true), depth_write(true), color_write(true), alpha_write(true)
{
  setObjectType (OBJTYPE_COMPOSITING_MODE);
}

CompositingMode:: ~CompositingMode ()
{
}

float CompositingMode:: getAlphaThreshold () const
{
    return alpha_threshold;
}

int CompositingMode:: getBlending () const
{
    return blending_mode;
}

float CompositingMode:: getDepthOffsetFactor () const
{
    return depth_offset.factor;
}

float CompositingMode:: getDepthOffsetUnits () const
{
    return depth_offset.units;
}

bool CompositingMode:: isAlphaWriteEnabled () const
{
    return alpha_write;
}


bool CompositingMode:: isColorWriteEnabled () const
{
    return color_write;
}

bool CompositingMode:: isDepthTestEnabled () const
{
    return depth_test;
}

bool CompositingMode:: isDepthWriteEnabled () const
{
    return depth_write;
}

void CompositingMode:: setAlphaThreshold (float threashold)
{
  alpha_threshold = threashold;
}

void CompositingMode:: setAlphaWriteEnable (bool enable)
{
  alpha_write = enable;
}

void CompositingMode:: setBlending (int mode)
{
  blending_mode = mode;
}

void CompositingMode:: setColorWriteEnable (bool enable)
{
  color_write = enable;
}

void CompositingMode:: setDepthOffset (float factor, float units)
{
  depth_offset = DepthOffset(factor, units);
}

void CompositingMode:: setDepthTestEnable (bool enable)
{
  depth_test = enable;
}

void CompositingMode:: setDepthWriteEnable (bool enable)
{
  depth_write = enable;
}

/**
 * Note: CompositingMode should be rendered only at second rendering pass(pass=2).
 * In other cases, do nothing.
 */
void CompositingMode:: render (int pass, int index) const
{
  if (pass != 2) {
    return;
  }

  //cout << "CompositingMode: render\n";

  if (depth_test) {
    glDepthFunc (GL_LESS);
  } else {
    glDepthFunc (GL_ALWAYS);
  }
  if (depth_write) {
    glDepthMask (GL_TRUE);
  } else {
    glDepthMask (GL_FALSE);
  }
  if (color_write && alpha_write) {
    glColorMask (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
  } else if (color_write && !alpha_write) {
    glColorMask (GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE);
  } else if (!color_write && alpha_write) {
    glColorMask (GL_FALSE, GL_FALSE, GL_FALSE, GL_TRUE);
  } else {
    glColorMask (GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
  }

  glEnable (GL_BLEND);
  switch (blending_mode) {
  case REPLACE: {
    glBlendFunc (GL_ONE, GL_ZERO);
    break;
  }
  case ALPHA_ADD: {
    glBlendFunc (GL_SRC_ALPHA, GL_ONE);
    break;
  }
  case ALPHA: {
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    break;
  }
  case MODULATE: {
    glBlendFunc (GL_DST_COLOR, GL_ZERO);
    break;
  }
  case MODULATE_X2: {
    glBlendFunc (GL_DST_COLOR, GL_SRC_COLOR);
    break;
  }
  default: {
    throw InternalException (__FILE__, __func__, "Blending mode is unknwon, mode=%d.", blending_mode);
  }
  }

  if (alpha_threshold > 0) {
    glEnable (GL_ALPHA_TEST);
    glAlphaFunc (GL_GREATER, alpha_threshold);
  }
  else {
    glDisable (GL_ALPHA_TEST);
  }

  if (depth_offset.factor > 0 || depth_offset.units > 0) {
    glEnable (GL_POLYGON_OFFSET_FILL);
    glPolygonOffset (depth_offset.factor, depth_offset.units);
  }
  else {
    glDisable (GL_POLYGON_OFFSET_FILL);
  }

}


std::ostream& CompositingMode:: print (std::ostream& out) const
{
  
  return out;
}

std::ostream& operator<< (std::ostream& out, const CompositingMode& cm)
{
  return cm.print(out);
}


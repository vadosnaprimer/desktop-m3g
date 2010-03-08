#include <strstream>
#include <iostream>
#include <vector>
#include "../CompositingMode.hpp"
using namespace std;
using namespace m3g;

void parse_CompositingMode (istrstream& iss, vector<Object3D*>& objs)
{
  bool depth_test_enabled;
  bool depth_write_enabled;
  bool color_write_enabled;
  bool alpha_write_enabled;
  unsigned char blending;
  unsigned char alpha_threshold;
  float depth_offset_factor;
  float depth_offset_units;

  iss.read ((char*)&depth_test_enabled, 1);
  iss.read ((char*)&depth_write_enabled, 1);
  iss.read ((char*)&color_write_enabled, 1);
  iss.read ((char*)&alpha_write_enabled, 1);
  iss.read ((char*)&blending, 1);
  iss.read ((char*)&alpha_threshold, 1);
  iss.read ((char*)&depth_offset_factor, 4);
  iss.read ((char*)&depth_offset_units, 4);

  CompositingMode* cmode = new CompositingMode;

  cmode->setDepthTestEnable (depth_test_enabled);
  cmode->setDepthWriteEnable (depth_offset_units);
  cmode->setColorWriteEnable (color_write_enabled);
  cmode->setAlphaWriteEnable (alpha_write_enabled);
  cmode->setBlending (blending);
  cmode->setAlphaThreshold (alpha_threshold);
  cmode->setDepthOffset (depth_offset_factor, depth_offset_units);

  objs.push_back (cmode);
}





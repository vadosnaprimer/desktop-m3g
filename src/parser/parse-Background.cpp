#include <strstream>
#include <iostream>
#include <vector>
#include "../Background.hpp"
#include "../Image2D.hpp"
#include "../m3gexcept.hpp"
#include "parse-Background.hpp"
#include "parse-Object3D.hpp"
using namespace std;
using namespace m3g;

void parse_Background (istrstream& iss, vector<Object3D*>& objs)
{
  Background* bg = new Background;

  parse_Object3D (iss, objs, bg);

  unsigned char r,g,b,a;
  iss.read ((char*)&r,1);
  iss.read ((char*)&g,1);
  iss.read ((char*)&b,1);
  iss.read ((char*)&a,1);
  int background_color = (a<<24) | (r<<16) | (g<<8) | (b<<0);
  bg->setColor (background_color);

  int background_image_index;
  iss.read ((char*)&background_image_index, 4);
  if (background_image_index > 0) {
    Image2D* img = dynamic_cast<Image2D*>(objs.at(background_image_index));
    bg->setImage (img);
  }

  unsigned char background_image_mode_x;
  unsigned char background_image_mode_y;
  iss.read ((char*)&background_image_mode_x, 1);
  iss.read ((char*)&background_image_mode_y, 1);
  bg->setImageMode (background_image_mode_x, background_image_mode_y);

  int crop_x;
  int crop_y;
  int crop_width;
  int crop_height;
  iss.read ((char*)&crop_x, 4);
  iss.read ((char*)&crop_y, 4);
  iss.read ((char*)&crop_width, 4);
  iss.read ((char*)&crop_height, 4);
  bg->setCrop (crop_x, crop_y, crop_width, crop_height);

  bool depth_clear_enabled;
  bool color_clear_enabled;
  iss.read ((char*)&depth_clear_enabled, 1);
  iss.read ((char*)&color_clear_enabled, 1);
  bg->setDepthClearEnable (depth_clear_enabled);
  bg->setColorClearEnable (color_clear_enabled);

  objs.push_back (bg);

  /*
  bg->print (cout);
  bg->Object3D::print (cout);
  */
}

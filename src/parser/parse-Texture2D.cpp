#include <strstream>
#include <iostream>
#include "../Texture2D.hpp"
#include "../Image2D.hpp"
#include "parse-Transformable.hpp"
using namespace std;
using namespace m3g;

void parse_Texture2D (istrstream& iss, vector<Object3D*>& objs)
{
  Transformable* dummy = new Transformable;
  parse_Transformable (iss, objs, dummy);

  Texture2D* tex = 0;

  unsigned int image_index;
  iss.read ((char*)&image_index, 4);
  if (image_index > 0) {
    Image2D* img = dynamic_cast<Image2D*>(objs.at(image_index));
    tex = new Texture2D (img);
  }

  unsigned char r,g,b;
  unsigned int  rgb;
  iss.read ((char*)&r, 1);
  iss.read ((char*)&g, 1);
  iss.read ((char*)&b, 1);
  rgb = (r<<16) | (g<<8) | (b<<0);
  tex->setBlendColor (rgb);

  unsigned char blending;
  iss.read ((char*)&blending, 1);
  tex->setBlending (blending);

  unsigned char wrapping_s;
  unsigned char wrapping_t;
  iss.read ((char*)&wrapping_s, 1);
  iss.read ((char*)&wrapping_t, 1);
  tex->setWrapping (wrapping_s, wrapping_t);

  unsigned char level_filter;
  unsigned char image_filter;
  iss.read ((char*)&level_filter, 1);
  iss.read ((char*)&image_filter, 1);
  tex->setFiltering (level_filter, image_filter);

  tex->print (cout);

  objs.push_back (tex);
}


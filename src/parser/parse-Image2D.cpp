#include <strstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "../Image2D.hpp"
#include "parse-Object3D.hpp"
#include "../Exception.hpp"
using namespace std;
using namespace m3g;


void parse_Image2D (istrstream& iss, vector<Object3D*>& objs)
{
  Object3D* dummy = new Object3D;
  parse_Object3D (iss, objs, dummy);

  Image2D* img = 0;

  unsigned char format;
  bool          is_mutable;
  unsigned int  width;
  unsigned int  height;

  iss.read ((char*)&format, 1);
  iss.read ((char*)&is_mutable, 1);
  iss.read ((char*)&width,  4);
  iss.read ((char*)&height, 4);

  if (is_mutable) {
    img = new Image2D (format, width, height);
    *(Object3D*)img = *dummy;
  }
  else {
    unsigned int palette_count;
    iss.read ((char*)&palette_count, 4);
    if (palette_count > 0) {
      throw NotImplementedException (__FILE__, __func__, "Paletted texture is not supported.");
    }

    unsigned int pixels_count;
    iss.read ((char*)&pixels_count, 4);

    char* pixels = new char[pixels_count];
    iss.read ((char*)pixels, pixels_count);

    img = new Image2D (format, width, height, pixels);
    *(Object3D*)img = *dummy;

    delete [] pixels;
  }

  img->print (cout);

   objs.push_back (img);
}

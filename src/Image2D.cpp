#include "Image2D.hpp"
#include "Exception.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace m3g;
using namespace std;

const int Image2D:: ALPHA;
const int Image2D:: LUMINANCE;
const int Image2D:: LUMINANCE_ALPHA;
const int Image2D:: RGB;
const int Image2D:: RGBA;


Image2D:: Image2D (int format_, int width_, int height_) : 
  format(format_), width(width_), height(height_),
  image(0), immutable(false)
{
  setObjectType (OBJTYPE_IMAGE2D);

  if (width <= 0 || height <= 0) {
    throw IllegalArgumentException (__FILE__, __func__, "Width or height is invalid, width=%f, height=%f.", width, height);
  }
  int bpp = format_to_bpp (format);

  image = new char [height*width*bpp];
  memset (image, 0, height*width*bpp);
}

Image2D:: Image2D (int format_, int width_, int height_, void* image_) : 
  format(format_), width(width_), height(height_), 
  image(0), immutable(true)
{
  setObjectType (OBJTYPE_IMAGE2D);

  if (width <= 0 || height <= 0) {
    throw IllegalArgumentException (__FILE__, __func__, "Width or height is invalid, width=%f, height=%f.", width, height);
  }
  if (image_ == NULL) {
    throw NullPointException (__FILE__, __func__, "Image is NULL.");
  }

  int bpp  = format_to_bpp (format);

  image = new char [height*width*bpp];
  memcpy (image, image_, height*width*bpp);
}

Image2D:: Image2D (int format_, int width_, int height_, void* image_, void* palette_) :
  format(format_), width(width_), height(height_), immutable(true)
{
  throw NotImplementedException (__FILE__, __func__, "Palleted image is not implemented. don't use this");
}

Image2D:: ~Image2D ()
{
  delete [] image;
}

Image2D* Image2D:: duplicate () const
{
  int bpp  = format_to_bpp (format);
  int size = height*width*bpp;

  Image2D* img = new Image2D (*this);
  img->image   = new char [size];
  memcpy (img->image, this->image, size);

  return img;
}

int Image2D:: getFormat () const
{
    return format;
}

int Image2D:: getHeight () const
{
    return height;
}

int Image2D:: getWidth () const
{
    return width;
}


bool Image2D:: isMutable () const
{
    return !immutable;
}

void Image2D:: set (int px, int py, int wid, int hei, void* image_)
{
  if (immutable) {
    throw IllegalStateException (__FILE__, __func__, "This image is immutable.");
  }
  if (px < 0 || px >= width || py < 0 || py >= height) {
    throw IllegalArgumentException (__FILE__, __func__, "Coordinate(px,py) is invalid, px=%d, py=%d.", px, py);
  }
  if (wid < 0 || wid > width || hei < 0 || hei > height) {
    throw IllegalArgumentException (__FILE__, __func__, "Size(width,height) is invalid, width=%d, height=%d.", wid, hei);
  }
  if (image == NULL) {
    throw NullPointException (__FILE__, __func__, "Image is NULL.");
  }

  int bpp = format_to_bpp (format);

  for (int y = py; y < py+hei; y++) {
    memcpy (image + y*width*bpp + px*bpp, (char*)image_ + (y-py)*wid*bpp, wid*bpp);
  }

}


 /**
  * 注意：OpenGLは左下が(0,0)、ppmは左上が(0,0)
  */
  void Image2D:: write_ppm (const char* name) const
  {
    int bpp = format_to_bpp (format);
    ofstream ofs(name);
    ofs << "P3\n" << width << " " << height << "\n255\n\n";
    for (int y = height-1; y >= 0; y--) {
      for (int x = 0; x < width; x++) {
	ofs << (int)*(image + y*width*bpp + x*bpp + 0) << " ";
	ofs << (int)*(image + y*width*bpp + x*bpp + 1) << " ";
	ofs << (int)*(image + y*width*bpp + x*bpp + 2) << " ";
      }
      ofs << "\n";
    }
    ofs << "\n";
  }

GLenum Image2D:: getOpenGLFormat () const
{
  switch (format) {
  case Image2D::ALPHA          : return GL_ALPHA;
  case Image2D::LUMINANCE      : return GL_LUMINANCE;
  case Image2D::LUMINANCE_ALPHA: return GL_LUMINANCE_ALPHA;
  case Image2D::RGB            : return GL_RGB;
  case Image2D::RGBA           : return GL_RGBA;
  default: throw InternalException (__FILE__, __func__, "Image format is unknwon, format=%d.", format);
  }

}

void* Image2D:: getOpenGLData () const
{
  return image;
}

int m3g::format_to_bpp (int format)
{
  switch (format) {
  case Image2D::ALPHA          : return 1;
  case Image2D::LUMINANCE      : return 1;
  case Image2D::LUMINANCE_ALPHA: return 2;
  case Image2D::RGB            : return 3;
  case Image2D::RGBA           : return 4;
  default: throw InternalException (__FILE__, __func__, "Format is unknwon, format=%d.", format);
  }
}

static 
const char* format_to_string (int format)
{
  switch (format) {
  case Image2D::ALPHA          : return "ALPHA";
  case Image2D::LUMINANCE      : return "LUMINANCE";
  case Image2D::LUMINANCE_ALPHA: return "LUMINANCE_ALPHA";
  case Image2D::RGB            : return "RGB";
  case Image2D::RGBA           : return "RGBA";
  default: return "Unknwon";
  }
}

 std::ostream& Image2D:: print (std::ostream& out) const
 {
   out << "Image2D: ";
   out << "  format="    << format_to_string(format);
   out << ", width="     << width;
   out << ", height="    << height;
   out << ", immutable=" << immutable;
   return out;
 }

std::ostream& operator<< (std::ostream& out, const Image2D& img)
{
  return img.print(out);
}


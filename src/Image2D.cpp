#include <iostream>
#include <fstream>
#include <cstring>
#include "Exception.hpp"
#include "Image2D.hpp"
using namespace m3g;
using namespace std;


Image2D:: Image2D (int format_, int width_, int height_) : 
  format(format_), width(width_), height(height_),
  image(0), bpp(0), immutable(false)
{
  setObjectType (OBJTYPE_IMAGE2D);

  if (width <= 0 || height <= 0) {
    throw IllegalArgumentException (__FILE__, __func__, "Width or height is invalid, width=%f, height=%f.", width, height);
  }
  bpp = format_to_bpp (format);

  image = new unsigned char [height*width*bpp];
  memset (image, 0, height*width*bpp);
}

Image2D:: Image2D (int format_, int width_, int height_, void* image_) : 
  format(format_), width(width_), height(height_), 
  image(0), bpp(0), immutable(true)
{
  if (width <= 0 || height <= 0) {
    throw IllegalArgumentException (__FILE__, __func__, "Width or height is invalid, width=%f, height=%f.", width, height);
  }
  if (image_ == 0) {
    throw NullPointException (__FILE__, __func__, "Image is NULL.");
  }

  bpp = format_to_bpp (format);
  image = new unsigned char [height*width*bpp];
  memcpy (image, image_, height*width*bpp);
}

Image2D:: Image2D (int format_, int width_, int height_, void* image_, void* palette_) :
  format(format_), width(width_), height(height_), bpp(0), immutable(true)
{
  throw NotImplementedException (__FILE__, __func__, "Palleted image is not implemented. don't use this");
}

Image2D:: ~Image2D ()
{
  if (image) {
    delete [] image;
    image = 0;
  }

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
  if (image == 0) {
    throw NullPointException (__FILE__, __func__, "Image is NULL.");
  }

  unsigned char* img = (unsigned char*)image_;

  for (int y = py; y < py+hei; y++) {
    memcpy (image + y*width*bpp + px*bpp, img + (y-py)*wid*bpp, wid*bpp);
  }

}


 /**
  * 注意：OpenGLは左下が(0,0)、ppmは左上が(0,0)
  */
  void Image2D:: write_ppm (const char* name) const
  {
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
  if (format == Image2D::ALPHA) {
    return GL_ALPHA;
  }
  else if (format == Image2D::LUMINANCE) {
    return GL_LUMINANCE;
  }
  else if (format == Image2D::LUMINANCE_ALPHA) {
    return GL_LUMINANCE_ALPHA;
  }
  else if (format == Image2D::RGB) {
    return GL_RGB;
   }
  else if (format == Image2D::RGBA) {
    return GL_RGBA;
  }
  else {
    throw InternalException (__FILE__, __func__, "Image format is unknwon, format=%d.", format);
  }

}

int Image2D:: format_to_bpp (int format) const
{
  switch (format) {
  case Image2D::ALPHA: {
    return 1;
  }
  case Image2D::LUMINANCE: {
    return 1;
  }
  case Image2D::LUMINANCE_ALPHA: {
    return 2;
  }
  case Image2D::RGB: {
    return 3;
  }
  case Image2D::RGBA: {
    return 4;
  }
  default: {
     throw InternalException (__FILE__, __func__, "Format is unknwon, format=%d.", format);
  }
  }
}

void* Image2D:: getImage () const
{
  return image;
}

static 
const char* format_to_string (int format)
{
  switch (format) {
  case Image2D::ALPHA:     return "ALPHA";
  case Image2D::LUMINANCE: return "LUMINANCE";
  case Image2D::LUMINANCE_ALPHA: return "LUMINANCE_ALPHA";
  case Image2D::RGB:       return "RGB";
  case Image2D::RGBA:      return "RGBA";
  default: return "Unknwon";
  }
}

 std::ostream& Image2D:: print (std::ostream& out) const
 {
   out << "Image2D: ";
   out << " format=" << format_to_string(format);
   out << " width=" << width;
   out << " height=" << height;
   out << " immutable=" << immutable;
   return out << "\n";
 }

std::ostream& operator<< (std::ostream& out, const Image2D& img)
{
  return img.print(out);
}


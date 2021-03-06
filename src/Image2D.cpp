#include "m3g/m3g-gl.hpp"
#include "m3g/Image2D.hpp"
#include "m3g/Exception.hpp"
#include "m3g/RenderState.hpp"
#include "m3g/stb_image_writer.hpp"
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
    format(format_), width(width_), height(height_), image(0), immutable(false)
{
    if (width <= 0 || height <= 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Width or height is invalid, width=%f, height=%f.", width, height);
    }
    if (format != Image2D::ALPHA && format != Image2D::LUMINANCE && format != Image2D::LUMINANCE_ALPHA &&
        format != Image2D::RGB   && format != Image2D::RGBA) {
        throw IllegalArgumentException (__FILE__, __func__, "Format is invalid, format=%d", format);
    }

    int bpp = format_to_bpp (format);
    image = new char [height*width*bpp];

    memset (image, 0, height*width*bpp);
}

Image2D:: Image2D (int format_, int width_, int height_, void* pixels) : 
    format(format_), width(width_), height(height_), image(0), immutable(true)
{
    if (width <= 0 || height <= 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Width or height is invalid, width=%f, height=%f.", width, height);
    }
    if (pixels == NULL) {
        throw NullPointerException (__FILE__, __func__, "Image is NULL.");
    }
    if (format != Image2D::ALPHA && format != Image2D::LUMINANCE && format != Image2D::LUMINANCE_ALPHA &&
        format != Image2D::RGB   && format != Image2D::RGBA) {
        throw IllegalArgumentException (__FILE__, __func__, "Format is invalid, format=%d", format);
    }

    int bpp  = format_to_bpp (format);
    image = new char [height*width*bpp];

    memcpy (image, pixels, height*width*bpp);
}

Image2D:: Image2D (int format_, int width_, int height_, unsigned char* pixels, void* palette) :
    format(format_), width(width_), height(height_), image(0), immutable(true)
{
    if (pixels == NULL || palette == NULL) {
        throw NullPointerException (__FILE__, __func__, "Palette or index is NULL.");
    }
    if (width <= 0 || height <= 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Width or height is invalid, width=%f, height=%f.", width, height);
    }
    if (format != Image2D::ALPHA && format != Image2D::LUMINANCE && format != Image2D::LUMINANCE_ALPHA &&
        format != Image2D::RGB   && format != Image2D::RGBA) {
        throw IllegalArgumentException (__FILE__, __func__, "Format is invalid, format=%d", format);
    }

    int bpp = format_to_bpp (format);
    image   = new char [height*width*bpp];
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = pixels[y*width + x];
            memcpy (image + (y*width + x)*bpp, (char*)palette + index*bpp, bpp);
        }
    }

    
}

Image2D:: ~Image2D ()
{
    delete [] image;
}

Image2D* Image2D:: duplicate () const
{
    return duplicate_xxx (NULL);
}

Image2D* Image2D:: duplicate_xxx (Object3D* obj) const
{
    Image2D* img = dynamic_cast<Image2D*>(obj);
    if (img == NULL) {
        if (immutable)
            img = new Image2D (format, width, height, image);
        else
            img = new Image2D (format, width, height);
    }
    Object3D:: duplicate_xxx (img);

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

void Image2D:: set (int px, int py, int wid, int hei, const void* pixels)
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
    if (pixels == NULL) {
        throw NullPointerException (__FILE__, __func__, "Image is NULL.");
    }

    int bpp = format_to_bpp (format);

    for (int y = py; y < py+hei; y++) {
        memcpy (image + y*width*bpp + px*bpp, (char*)pixels + (y-py)*wid*bpp, wid*bpp);
    }

}


/**
 * 注意：OpenGLは左下が(0,0)
 */
void Image2D:: writePNG (const char* name) const
{
    if (name == NULL) {
        throw NullPointerException (__FILE__, __func__, "File name is NULL.");
    }
    int comp = format_to_bpp(format);
    int ret  = stbi_write_png (name, width, height, comp, image, width*comp);
    if (ret == 0) {
        throw IOException (__FILE__, __func__, "Can't write png, name=%s.", name);
    }
}

unsigned int Image2D:: getOpenGLFormat () const
{
    switch (format) {
    case Image2D::ALPHA          : return GL_ALPHA;
    case Image2D::LUMINANCE      : return GL_LUMINANCE;
    case Image2D::LUMINANCE_ALPHA: return GL_LUMINANCE_ALPHA;
    case Image2D::RGB            : return GL_RGB;
    case Image2D::RGBA           : return GL_RGBA;
    default: throw InternalException (__FILE__, __func__, "Image format is unknown, format=%d.", format);
    }

}

void* Image2D:: getOpenGLPointer () const
{
    return image;
}

/**
 * メモ： (非公開)この関数は通常のrender()関数と異なり、
 *        現在のフレームバッファーの内容をこのImag2Dへ取り込む.
 *        別の名前にしたほうがいいだろう。
 */
void Image2D:: render_xxx (RenderState& state) const
{
    unsigned int gl_format = getOpenGLFormat ();
    unsigned int gl_type   = GL_UNSIGNED_BYTE;
    glReadPixels (0, 0, width, height, gl_format, gl_type, (unsigned char*)image);
}


int m3g::format_to_bpp (int format)
{
    switch (format) {
    case Image2D::ALPHA          : return 1;
    case Image2D::LUMINANCE      : return 1;
    case Image2D::LUMINANCE_ALPHA: return 2;
    case Image2D::RGB            : return 3;
    case Image2D::RGBA           : return 4;
    default: throw InternalException (__FILE__, __func__, "Format is unknown, format=%d.", format);
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
    default: return "Unknown";
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


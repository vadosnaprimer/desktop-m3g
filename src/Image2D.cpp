#include "m3g/m3g-gl.hpp"
#include "m3g/Image2D.hpp"
#include "m3g/Exception.hpp"
#include "m3g/RenderState.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <png.h>
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
    Image2D* img;
    if (immutable)
        img = new Image2D (format, width, height, image);
    else
        img = new Image2D (format, width, height);
    img->Object3D:: copy (img);
    img->Image2D :: copy (img);
    return img;
}

void Image2D:: copy (Image2D* img) const
{
    if (img == NULL) {
        throw NullPointerException (__FILE__, __func__, "Image is NULL.");
    }
    // すべてコンストラクタで設定済み
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

void Image2D:: set (int px, int py, int wid, int hei, void* pixels)
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

    png_structp png_ptr;
    png_infop   info_ptr;
	
    FILE* fp = fopen (name, "wb");
    if (!fp) {
        throw IOException (__FILE__, __func__, "Can't open file, name=%s.", name);
    }
    png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, 0, 0, 0);
    if (!png_ptr) {
        fclose (fp);
        throw InternalException (__FILE__, __func__, "Can't crate png struct.");
    }

    info_ptr = png_create_info_struct (png_ptr);
    if (!info_ptr) {
        fclose (fp);
        png_destroy_write_struct (&png_ptr, 0);
        throw InternalException (__FILE__, __func__, "Can't create info struct.");
    }

    if (setjmp (png_jmpbuf(png_ptr))) {
        fclose (fp);
        png_destroy_write_struct (&png_ptr, &info_ptr);
        throw InternalException (__FILE__, __func__, "Can't decode png.");
    }

    png_init_io (png_ptr, fp);

    info_ptr->width     = width;
    info_ptr->height    = height;
    info_ptr->bit_depth = 8;
    switch (format) {
    case ALPHA          : info_ptr->color_type = PNG_COLOR_TYPE_GRAY      ; break;
    case LUMINANCE      : info_ptr->color_type = PNG_COLOR_TYPE_GRAY      ; break;
    case LUMINANCE_ALPHA: info_ptr->color_type = PNG_COLOR_TYPE_GRAY_ALPHA; break;
    case RGB            : info_ptr->color_type = PNG_COLOR_TYPE_RGB       ; break;
    case RGBA           : info_ptr->color_type = PNG_COLOR_TYPE_RGB_ALPHA ; break;
    default: throw InternalException (__FILE__, __func__, "Unknown format=%d.", format);
    }
    info_ptr->interlace_type   = PNG_INTERLACE_NONE;
    info_ptr->compression_type = PNG_COMPRESSION_TYPE_DEFAULT;
    info_ptr->filter_type      = PNG_FILTER_TYPE_DEFAULT;

    int bpp = format_to_bpp (format);
    png_byte** row_pointers = (png_byte**)new png_byte* [height];
    for (int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*)&image[(height-1-y)*width*bpp];
    }
    png_set_rows  (png_ptr, info_ptr, row_pointers);
    png_write_png (png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, 0);

    delete [] row_pointers;
    png_destroy_write_struct (&png_ptr, 0);
    fclose (fp);
    
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
 * (非公開) この関数は現在のフレームバッファーの内容をこのImag2Dへコピーする.
 */
void Image2D:: render (RenderState& state) const
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


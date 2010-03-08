#include <new>
#include "ruby.h"
#include "Image2D.hpp"
using namespace m3g;


VALUE ruby_Image2D_free (Image2D* ptr)
{
    ptr->~Image2D ();
    ruby_xfree (ptr);
}

VALUE ruby_Image2D_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Image2D));
    return Data_Wrap_Struct (self, NULL, ruby_Image2D_free, p);
}

VALUE ruby_Image2D_initialize (int argc, VALUE* argv, VALUE self)
{
    Image2D* p;
    Data_Get_Struct (self, Image2D, p);
    new (p) Image2D (Image2D::RGB,256,256);
    return Qnil;
}

VALUE ruby_Image2D_get_format (VALUE self)
{
    return Qnil;
}

VALUE ruby_Image2D_get_height (VALUE self)
{
    return Qnil;
}

VALUE ruby_Image2D_get_width (VALUE self)
{
    return Qnil;
}

VALUE ruby_Image2D_is_mutable (VALUE self)
{
    return Qnil;
}

VALUE ruby_Image2D_set (VALUE self, VALUE val_x, VALUE val_y, VALUE val_width, VALUE val_height, VALUE val_image)
{
    return Qnil;
}

void register_Image2D (VALUE rb_cImage2D)
{
     // Image2D
     rb_define_const (rb_cImage2D, "ALPHA",           INT2FIX(Image2D::ALPHA));
     rb_define_const (rb_cImage2D, "LUMINANCE",       INT2FIX(Image2D::LUMINANCE));
     rb_define_const (rb_cImage2D, "LUMINANCE_ALPHA", INT2FIX(Image2D::LUMINANCE_ALPHA));
     rb_define_const (rb_cImage2D, "RGB",             INT2FIX(Image2D::RGB));
     rb_define_const (rb_cImage2D, "RGBA",            INT2FIX(Image2D::RGBA));

     rb_define_alloc_func (rb_cImage2D, ruby_Image2D_allocate);
     rb_define_private_method (rb_cImage2D, "initialize", (VALUE(*)(...))ruby_Image2D_initialize, -1);

     rb_define_method (rb_cImage2D, "format",  (VALUE(*)(...))ruby_Image2D_get_format, 0);
     rb_define_method (rb_cImage2D, "height",  (VALUE(*)(...))ruby_Image2D_get_height, 0);
     rb_define_method (rb_cImage2D, "width",   (VALUE(*)(...))ruby_Image2D_get_width,  0);
     rb_define_method (rb_cImage2D, "mutable?", (VALUE(*)(...))ruby_Image2D_is_mutable,0);
     rb_define_method (rb_cImage2D, "set",      (VALUE(*)(...))ruby_Image2D_set,       5);
}

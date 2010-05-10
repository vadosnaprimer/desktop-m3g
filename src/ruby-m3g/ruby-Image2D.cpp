#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;


VALUE ruby_Image2D_free (Image2D* ptr)
{
    ptr->~Image2D ();
    ruby_xfree (ptr);
}

VALUE ruby_Image2D_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Image2D));
    return Data_Wrap_Struct (self, 0, ruby_Image2D_free, p);
}

VALUE ruby_Image2D_initialize (int argc, VALUE* argv, VALUE self)
{
    Image2D* p;
    Data_Get_Struct (self, Image2D, p);

    VALUE val_arg1, val_arg2, val_arg3, val_arg4, val_arg5;
    int num = rb_scan_args (argc, argv, "32", &val_arg1, &val_arg2, &val_arg3, &val_arg4, &val_arg5);

    switch (num) {
    case 3: {
      int format = FIX2INT (val_arg1);
      int width  = FIX2INT (val_arg2);
      int height = FIX2INT (val_arg3);
      new (p) Image2D (format, width, height);
      break;
    }
    case 4: {
      int format = FIX2INT (val_arg1);
      int width  = FIX2INT (val_arg2);
      int height = FIX2INT (val_arg3);
      void* image = (void*)STR2CSTR (val_arg4);
      new (p) Image2D (format, width, height, image);
      break;
    }
    case 5: {
      int format = FIX2INT (val_arg1);
      int width = FIX2INT (val_arg2);
      int height = FIX2INT (val_arg3);
      void* image = (void*)STR2CSTR (val_arg4);
      void* palette = (void*)STR2CSTR (val_arg5);
      new (p) Image2D (format, width, height, image, palette);
      break;
    }
    default: {
      // エラー
    }
    }

    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_Image2D_get_format (VALUE self)
{
  Image2D* p;
  int format;

  Data_Get_Struct (self, Image2D, p);
  
  format = p->getFormat ();

  return INT2FIX(format);
}

VALUE ruby_Image2D_get_height (VALUE self)
{
  Image2D* p;
  int height;

  Data_Get_Struct (self, Image2D, p);
  
  height = p->getHeight ();

  return INT2FIX(height);
}

VALUE ruby_Image2D_get_width (VALUE self)
{
  Image2D* p;
  int width;

  Data_Get_Struct (self, Image2D, p);
  
  width = p->getWidth ();

  return INT2FIX(width);
}

VALUE ruby_Image2D_is_mutable (VALUE self)
{
  Image2D* p;
  bool mutabl;
  Data_Get_Struct (self, Image2D, p);
  
  mutabl = p->isMutable();

  if (mutabl)
    return Qtrue;
  else
    return Qfalse;
}

VALUE ruby_Image2D_set (VALUE self, VALUE val_x, VALUE val_y, VALUE val_width, VALUE val_height, VALUE val_image)
{
  Image2D* p;
  int      x, y, width, height;
  void*    image;

  Data_Get_Struct (self, Image2D, p);
  x      = FIX2INT (val_x);
  y      = FIX2INT (val_y);
  width  = FIX2INT (val_width);
  height = FIX2INT (val_height);
  image  = (void*)STR2CSTR (val_image);

  p->set (x, y, width, height, image);

  return Qnil;
}

void register_Image2D ()
{
     // Image2D
    rb_cImage2D = rb_define_class_under (rb_mM3G, "Image2D",             rb_cObject3D);

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

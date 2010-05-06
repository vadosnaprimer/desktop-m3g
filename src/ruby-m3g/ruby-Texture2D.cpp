#include <iostream>
#include "ruby.h"
#include "ruby-m3g.hpp"
#include "m3g.hpp"
using namespace m3g;
using namespace std;

namespace {
  VALUE rb_cTexture2D_Filter;
  VALUE rb_cTexture2D_Wrapping;
}


VALUE ruby_Texture2D_free (Texture2D* ptr)
{
    ptr->~Texture2D ();
    ruby_xfree (ptr);
}

VALUE ruby_Texture2D_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Texture2D));
    return Data_Wrap_Struct (self, 0, ruby_Texture2D_free, p);
}

VALUE ruby_Texture2D_initialize (VALUE self, VALUE val_image)
{
    Texture2D* p;
    Image2D* img;
    Data_Get_Struct (self, Texture2D, p);
    Data_Get_Struct (val_image, Image2D, img);
    new (p) Texture2D (img);
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_Texture2D_get_blend_color (VALUE self)
{
    Texture2D* p;
    int argb;

    Data_Get_Struct (self, Texture2D, p);
    argb = p->getBlendColor ();

    return INT2FIX(argb);
}

VALUE ruby_Texture2D_get_blending (VALUE self)
{
    Texture2D* p;
    int mode;

    Data_Get_Struct (self, Texture2D, p);
    mode = p->getBlending();

    return INT2FIX(mode);
}

VALUE ruby_Texture2D_get_image (VALUE self)
{
    Texture2D* p;
    Image2D* img;
    Data_Get_Struct (self, Texture2D, p);
    img = p->getImage();

    return img ? (VALUE)img->getExportedEntity() : Qnil;
}

VALUE ruby_Texture2D_get_filter (VALUE self)
{
    Texture2D* p;
    Texture2D::Filter* filter;
    VALUE val_filter;

    Data_Get_Struct (self, Texture2D, p);
    val_filter = Data_Make_Struct (rb_cTexture2D_Filter, Texture2D::Filter, 0, -1, filter);
    
    filter->image = p->getImageFilter ();
    filter->level = p->getLevelFilter ();

    return val_filter;
}


VALUE ruby_Texture2D_get_wrapping (VALUE self)
{
    Texture2D* p;
    Texture2D::Wrapping* wrapping;
    VALUE val_wrapping;

    Data_Get_Struct (self, Texture2D, p);
    val_wrapping = Data_Make_Struct (rb_cTexture2D_Wrapping, Texture2D::Wrapping, 0, -1, wrapping);
      
    wrapping->s = p->getWrappingS();
    wrapping->t = p->getWrappingT();

    return val_wrapping;
}

VALUE ruby_Texture2D_set_blend_color (VALUE self, VALUE val_rgb)
{
    Texture2D* p;
    int rgb;

    Data_Get_Struct (self, Texture2D, p);
    rgb = FIX2INT(val_rgb);

    p->setBlendColor (rgb);

    return Qnil;
}

VALUE ruby_Texture2D_set_blending (VALUE self, VALUE val_func)
{
    Texture2D* p;
    int func;

    Data_Get_Struct (self, Texture2D, p);
    func = FIX2INT (val_func);

    p->setBlending (func);

    return Qnil;
}

VALUE ruby_Texture2D_set_filtering (VALUE self, VALUE val_filter)
{
  VALUE val_level = rb_ary_entry(val_filter, 0);
  VALUE val_image = rb_ary_entry(val_image, 0);
  Texture2D* p;
  Data_Get_Struct (self, Texture2D, p);
  int level = FIX2INT (val_level);
  int image = FIX2INT (val_image);

  p->setFiltering (level, image);

  return Qnil;
}

VALUE ruby_Texture2D_set_image (VALUE self, VALUE val_image)
{
    Texture2D* p;
    Image2D* img;

    Data_Get_Struct (self, Texture2D, p);
    Data_Get_Struct (val_image, Image2D, img);

    p->setImage (img);

    return Qnil;
}

VALUE ruby_Texture2D_set_wrapping (VALUE self, VALUE val_wrapping)
{
  VALUE val_wrap_s = rb_ary_entry (val_wrapping, 0);
  VALUE val_wrap_t = rb_ary_entry (val_wrapping, 1);
    int wrap_s = FIX2INT (val_wrap_s);
    int wrap_t = FIX2INT (val_wrap_t);
    Texture2D* p;
    Data_Get_Struct (self, Texture2D, p);

    p->setWrapping (wrap_s,wrap_t);

    return Qnil;
}

/**
 * Texture2D:: Filter
 */

VALUE ruby_Texture2D_Filter_allocate (VALUE self)
{
  void* p = ruby_xmalloc (sizeof(Texture2D::Filter));
  return Data_Wrap_Struct (self, 0, -1, p);
}

VALUE ruby_Texture2D_Filter_initialize (VALUE self, VALUE val_level, VALUE val_image)
{
  Texture2D::Filter* p;
    Data_Get_Struct (self, Texture2D::Filter, p);
    p->level = FIX2INT (val_level);
    p->image = FIX2INT (val_image);
    return self;
}

VALUE ruby_Texture2D_Filter_get_level (VALUE self)
{
  Texture2D::Filter* p;
    Data_Get_Struct (self, Texture2D::Filter, p);
    return INT2FIX(p->level);
}

VALUE ruby_Texture2D_Filter_get_image (VALUE self)
{
  Texture2D::Filter* p;
    Data_Get_Struct (self, Texture2D::Filter, p);
    return INT2FIX(p->image);
}

/**
 * Texture2D:: Wrapping
 */


VALUE ruby_Texture2D_Wrapping_allocate (VALUE self)
{
  void* p = ruby_xmalloc (sizeof(Texture2D::Wrapping));
  return Data_Wrap_Struct (self, 0, -1, p);
}

VALUE ruby_Texture2D_Wrapping_initialize (VALUE self, VALUE val_wrap_s, VALUE val_wrap_t)
{
  Texture2D::Wrapping* p;
    Data_Get_Struct (self, Texture2D::Wrapping, p);
    p->s = FIX2INT(val_wrap_s);
    p->t = FIX2INT(val_wrap_t);
    return self;
}

VALUE ruby_Texture2D_Wrapping_get_s (VALUE self)
{
  Texture2D::Wrapping* p;
    Data_Get_Struct (self, Texture2D::Wrapping, p);
    return INT2FIX(p->s);
}

VALUE ruby_Texture2D_Wrapping_get_t (VALUE self)
{
  Texture2D::Wrapping* p;
    Data_Get_Struct (self, Texture2D::Wrapping, p);
    return INT2FIX(p->t);
}

void register_Texture2D ()
{
     // Texture2D
     rb_define_const (rb_cTexture2D, "FILTER_BASE_LEVEL", INT2FIX(Texture2D::FILTER_BASE_LEVEL));
     rb_define_const (rb_cTexture2D, "FILTER_LINEAR",     INT2FIX(Texture2D::FILTER_LINEAR));
     rb_define_const (rb_cTexture2D, "FILTER_NEAREST",    INT2FIX(Texture2D::FILTER_NEAREST));
     rb_define_const (rb_cTexture2D, "FUNC_ADD",          INT2FIX(Texture2D::FUNC_ADD));
     rb_define_const (rb_cTexture2D, "FUNC_BLEND",        INT2FIX(Texture2D::FUNC_BLEND));
     rb_define_const (rb_cTexture2D, "FUNC_DECAL",        INT2FIX(Texture2D::FUNC_DECAL));
     rb_define_const (rb_cTexture2D, "FUNC_MODULATE",     INT2FIX(Texture2D::FUNC_MODULATE));
     rb_define_const (rb_cTexture2D, "FUNC_REPLACE",      INT2FIX(Texture2D::FUNC_REPLACE));
     rb_define_const (rb_cTexture2D, "WRAP_CLAMP",        INT2FIX(Texture2D::WRAP_CLAMP));
     rb_define_const (rb_cTexture2D, "WRAP_REPEAT",       INT2FIX(Texture2D::WRAP_REPEAT));

     rb_define_alloc_func (rb_cTexture2D, ruby_Texture2D_allocate);
     rb_define_private_method (rb_cTexture2D, "initialize", (VALUE(*)(...))ruby_Texture2D_initialize, 1);

     rb_define_method (rb_cTexture2D, "blend_color",   (VALUE(*)(...))ruby_Texture2D_get_blend_color, 0);
     rb_define_method (rb_cTexture2D, "blending",      (VALUE(*)(...))ruby_Texture2D_get_blending,    0);
     rb_define_method (rb_cTexture2D, "filter",        (VALUE(*)(...))ruby_Texture2D_get_filter, 0);
     rb_define_method (rb_cTexture2D, "wrapping",      (VALUE(*)(...))ruby_Texture2D_get_wrapping, 0);
     rb_define_method (rb_cTexture2D, "blend_color=",  (VALUE(*)(...))ruby_Texture2D_set_blend_color, 1);
     rb_define_method (rb_cTexture2D, "blending=",     (VALUE(*)(...))ruby_Texture2D_set_blending,  1);
     rb_define_method (rb_cTexture2D, "filtering=",    (VALUE(*)(...))ruby_Texture2D_set_filtering, 1);
     rb_define_method (rb_cTexture2D, "image=",        (VALUE(*)(...))ruby_Texture2D_set_image,     1);
     rb_define_method (rb_cTexture2D, "wrapping=",     (VALUE(*)(...))ruby_Texture2D_set_wrapping,  1);

     // Texture2D::Filtering
     rb_cTexture2D_Filter = rb_define_class_under (rb_cTexture2D, "Filter", rb_cObject);
     rb_define_alloc_func (rb_cTexture2D_Filter, ruby_Texture2D_Filter_allocate);
     rb_define_private_method (rb_cTexture2D_Filter, "initialize", (VALUE(*)(...))ruby_Texture2D_Filter_initialize, 2);

     rb_define_method (rb_cTexture2D_Filter, "level",      (VALUE(*)(...))ruby_Texture2D_Filter_get_level, 0);
     rb_define_method (rb_cTexture2D_Filter, "image",      (VALUE(*)(...))ruby_Texture2D_Filter_get_image, 0);


     // Texture2D::Wrapping
     rb_cTexture2D_Wrapping = rb_define_class_under (rb_cTexture2D, "Wrapping", rb_cObject);
     rb_define_alloc_func (rb_cTexture2D_Wrapping, ruby_Texture2D_Wrapping_allocate);
     rb_define_private_method (rb_cTexture2D_Wrapping, "initialize", (VALUE(*)(...))ruby_Texture2D_Wrapping_initialize, 2);

     rb_define_method (rb_cTexture2D_Wrapping, "s",      (VALUE(*)(...))ruby_Texture2D_Wrapping_get_s, 0);
     rb_define_method (rb_cTexture2D_Wrapping, "t",      (VALUE(*)(...))ruby_Texture2D_Wrapping_get_t, 0);
}

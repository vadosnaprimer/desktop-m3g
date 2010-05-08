#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

namespace {
  VALUE rb_cBackground_ImageMode;
  VALUE rb_cBackground_CropRect;
}


VALUE ruby_Background_free (Background* ptr)
{
    ptr->~Background ();
    ruby_xfree (ptr);
}

VALUE ruby_Background_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Background));
    return Data_Wrap_Struct (self, 0, ruby_Background_free, p);
}

VALUE ruby_Background_initialize (VALUE self)
{
    Background* p;
    Data_Get_Struct (self, Background, p);
    new (p) Background;
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_Background_get_color (VALUE self)
{
    Background* p;
    int color;

    Data_Get_Struct (self, Background, p);

    color = p->getColor ();

    return INT2FIX(color);
}

VALUE ruby_Background_get_crop (VALUE self)
{
  Background* p;
  Data_Get_Struct (self, Background, p);

  Background::CropRect* crop;
  VALUE val_crop = Data_Make_Struct (rb_cBackground_CropRect, Background::CropRect, 0, -1, crop);
  
    crop->x = p->getCropX();
    crop->y = p->getCropY();
    crop->width = p->getCropWidth();
    crop->height = p->getCropHeight();

    return val_crop;
}

VALUE ruby_Background_get_image (VALUE self)
{
  Background* p;
  Image2D* img;

  Data_Get_Struct (self, Background, p);

  img = p->getImage ();

  if (img)
    return (VALUE)img->getExportedEntity();
  else
    return Qnil;
}

VALUE ruby_Background_get_image_mode (VALUE self)
{
  Background* p;
  Data_Get_Struct (self, Background, p);
  Background::ImageMode* mode;
  VALUE val_mode = Data_Make_Struct (rb_cBackground_ImageMode, Background::ImageMode, 0, -1, mode);
  
  mode->x = p->getImageModeX();
  mode->y = p->getImageModeY();

  return val_mode;
}

VALUE ruby_Background_is_color_clear_enabled (VALUE self)
{
  Background* p;
  bool ret;

  Data_Get_Struct (self, Background, p);

  ret = p->isColorClearEnabled ();

  if (ret)
    return Qtrue;
  else
    return Qfalse;
}

VALUE ruby_Background_is_depth_clear_enabled (VALUE self)
{
  Background* p;
  bool ret;

  Data_Get_Struct (self, Background, p);

  ret = p->isDepthClearEnabled ();

  if (ret)
    return Qtrue;
  else
    return Qfalse;
}

VALUE ruby_Background_set_color (VALUE self, VALUE val_argb)
{
  Background* p;
  Data_Get_Struct (self, Background, p);
  int argb = FIX2INT(val_argb);

  p->setColor (argb);

  return Qnil;
}

VALUE ruby_Background_set_color_clear_enable (VALUE self, VALUE val_enable)
{
  Background* p;
  bool enable;

  Data_Get_Struct (self, Background, p);
  enable = (val_enable == Qtrue) ? true : false;

  p->setColorClearEnable (enable);

  return Qnil;
}

VALUE ruby_Background_set_crop (VALUE self, VALUE val_crop)
{
  VALUE val_x      = rb_ary_entry(val_crop, 0);
  VALUE val_y      = rb_ary_entry(val_crop, 1);
  VALUE val_width  = rb_ary_entry(val_crop, 2);
  VALUE val_height = rb_ary_entry(val_crop, 3);
  Background* p;
  Data_Get_Struct (self, Background, p);
  float x      = NUMERIC2FLOAT (val_x);
  float y      = NUMERIC2FLOAT (val_y);
  float width  = NUMERIC2FLOAT (val_width);
  float height = NUMERIC2FLOAT (val_height);

  p->setCrop (x, y, width, height);

  return Qnil;
}

VALUE ruby_Background_set_depth_clear_enable (VALUE self, VALUE val_enable)
{
  Background* p;
  bool enable;

  Data_Get_Struct (self, Background, p);
  enable = (val_enable == Qtrue) ? true : false;

  p->setDepthClearEnable (enable);

  return Qnil;
}

VALUE ruby_Background_set_image (VALUE self, VALUE val_image)
{
  Background* p;
  Image2D* img;

  Data_Get_Struct (self, Background, p);
  Data_Get_Struct (val_image, Image2D, img);

  p->setImage (img);

  return Qnil;
}

VALUE ruby_Background_set_image_mode (VALUE self, VALUE val_mode)
{
  VALUE val_x = rb_ary_entry(val_mode, 0);
  VALUE val_y = rb_ary_entry(val_mode, 1);
  Background* p;
  Data_Get_Struct (self, Background, p);
  float x = NUMERIC2FLOAT(val_x);
  float y = NUMERIC2FLOAT(val_y);

  p->setImageMode (x, y);

  return Qnil;
}


/**
 * Background::ImageMode
 */
VALUE ruby_Background_ImageMode_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Background::ImageMode));
    return Data_Wrap_Struct (self, 0, -1, p);
}

VALUE ruby_Background_ImageMode_initialize (VALUE self)
{
  Background::ImageMode* p;
  Data_Get_Struct (self, Background::ImageMode, p);
  return self;
}

VALUE ruby_Background_ImageMode_get_x (VALUE self)
{
  Background::ImageMode* p;
  Data_Get_Struct (self, Background::ImageMode, p);
  return INT2FIX(p->x);
}

VALUE ruby_Background_ImageMode_get_y (VALUE self)
{
  Background::ImageMode* p;
  Data_Get_Struct (self, Background::ImageMode, p);
  return INT2FIX(p->y);
}

/**
 * Background::Crop
 */
VALUE ruby_Background_CropRect_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Background::CropRect));
    return Data_Wrap_Struct (self, 0, -1, p);
}

VALUE ruby_Background_CropRect_initialize (VALUE self)
{
  Background::CropRect* p;
  Data_Get_Struct (self, Background::CropRect, p);
  return self;
}

VALUE ruby_Background_CropRect_get_x (VALUE self)
{
  Background::CropRect* p;
  Data_Get_Struct (self, Background::CropRect, p);
  return INT2FIX(p->x);
}

VALUE ruby_Background_CropRect_get_y (VALUE self)
{
  Background::CropRect* p;
  Data_Get_Struct (self, Background::CropRect, p);
  return INT2FIX(p->y);
}

VALUE ruby_Background_CropRect_get_width (VALUE self)
{
  Background::CropRect* p;
  Data_Get_Struct (self, Background::CropRect, p);
  return INT2FIX(p->width);
}

VALUE ruby_Background_CropRect_get_height (VALUE self)
{
  Background::CropRect* p;
  Data_Get_Struct (self, Background::CropRect, p);
  return INT2FIX(p->height);
}


void register_Background ()
{
    // Background
    rb_define_const (rb_cBackground, "BORDER", INT2FIX(Background::BORDER)); 
    rb_define_const (rb_cBackground, "REPEAT", INT2FIX(Background::REPEAT)); 

    rb_define_alloc_func (rb_cBackground, ruby_Background_allocate);
    rb_define_private_method (rb_cBackground, "initialize", (VALUE(*)(...))ruby_Background_initialize, 0);

    rb_define_method (rb_cBackground, "color",               (VALUE(*)(...))ruby_Background_get_color, 0); 
    rb_define_method (rb_cBackground, "crop",                (VALUE(*)(...))ruby_Background_get_crop, 0); 
    rb_define_method (rb_cBackground, "image",               (VALUE(*)(...))ruby_Background_get_image, 0); 
    rb_define_method (rb_cBackground, "image_mode",          (VALUE(*)(...))ruby_Background_get_image_mode, 0); 
    rb_define_method (rb_cBackground, "color_clear_enabled?", (VALUE(*)(...))ruby_Background_is_color_clear_enabled, 0); 
    rb_define_method (rb_cBackground, "depth_clear_enabled?", (VALUE(*)(...))ruby_Background_is_depth_clear_enabled, 0); 
    rb_define_method (rb_cBackground, "color=",               (VALUE(*)(...))ruby_Background_set_color, 1); 
    rb_define_method (rb_cBackground, "color_clear_enable=",  (VALUE(*)(...))ruby_Background_set_color_clear_enable, 1); 
    rb_define_method (rb_cBackground, "crop=",                (VALUE(*)(...))ruby_Background_set_crop, 1); 
    rb_define_method (rb_cBackground, "depth_clear_enable=",  (VALUE(*)(...))ruby_Background_set_depth_clear_enable, 1); 
    rb_define_method (rb_cBackground, "image=",               (VALUE(*)(...))ruby_Background_set_image, 1); 
    rb_define_method (rb_cBackground, "image_mode=",          (VALUE(*)(...))ruby_Background_set_image_mode, 1); 

    // Background::ImageMode
     rb_cBackground_ImageMode  = rb_define_class_under (rb_cBackground, "ImageMode", rb_cObject);

    rb_define_alloc_func (rb_cBackground_ImageMode, ruby_Background_ImageMode_allocate);
    rb_define_private_method (rb_cBackground_ImageMode, "initialize", (VALUE(*)(...))ruby_Background_ImageMode_initialize, 0);

    rb_define_method (rb_cBackground_ImageMode, "x",               (VALUE(*)(...))ruby_Background_ImageMode_get_x, 0); 
    rb_define_method (rb_cBackground_ImageMode, "y",               (VALUE(*)(...))ruby_Background_ImageMode_get_y, 0); 


    // background::CropRect
     rb_cBackground_CropRect  = rb_define_class_under (rb_cBackground, "CropRect", rb_cObject);

    rb_define_alloc_func (rb_cBackground_CropRect, ruby_Background_CropRect_allocate);
    rb_define_private_method (rb_cBackground_CropRect, "initialize", (VALUE(*)(...))ruby_Background_CropRect_initialize, 0);

    rb_define_method (rb_cBackground_CropRect, "x",               (VALUE(*)(...))ruby_Background_CropRect_get_x, 0); 
    rb_define_method (rb_cBackground_CropRect, "y",               (VALUE(*)(...))ruby_Background_CropRect_get_y, 0); 
    rb_define_method (rb_cBackground_CropRect, "width",           (VALUE(*)(...))ruby_Background_CropRect_get_width, 0); 
    rb_define_method (rb_cBackground_CropRect, "height",          (VALUE(*)(...))ruby_Background_CropRect_get_height, 0); 


}

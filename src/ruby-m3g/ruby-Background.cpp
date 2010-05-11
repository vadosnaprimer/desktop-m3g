#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

namespace {
    struct ImageModeAccessor {
        Background* background;
    };
    struct CropAccessor {
        Background* background;
    };
    VALUE rb_cBackground_ImageModeAccessor;
    VALUE rb_cBackground_CropAccessor;
}


VALUE ruby_Background_free (Background* ptr)
{
    __TRY__;
    ptr->~Background ();
    __CATCH__;
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
    __TRY__;
    new (p) Background;
    __CATCH__;
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_Background_get_color (VALUE self)
{
    Background* p;
    Data_Get_Struct (self, Background, p);
    int color;
    __TRY__;
    color = p->getColor ();
    __CATCH__;
    return INT2NUM(color);
}

VALUE ruby_Background_get_crop (VALUE self)
{
    Background* p;
    Data_Get_Struct (self, Background, p);
    CropAccessor* accessor;
    VALUE val_accessor = Data_Make_Struct (rb_cBackground_CropAccessor, CropAccessor, 0, -1, accessor);
    accessor->background = p;
    return val_accessor;
}

VALUE ruby_Background_get_image (VALUE self)
{
    Background* p;
    Data_Get_Struct (self, Background, p);
    Image2D* img;
    __TRY__;
    img = p->getImage ();
    __CATCH__;
    return img ? (VALUE)img->getExportedEntity() : Qnil;
}

VALUE ruby_Background_get_image_mode (VALUE self)
{
    Background* p;
    Data_Get_Struct (self, Background, p);
    ImageModeAccessor* accessor;
    VALUE val_accessor = Data_Make_Struct (rb_cBackground_ImageModeAccessor, ImageModeAccessor, 0, -1, accessor);
    accessor->background = p;
    return val_accessor;
}

VALUE ruby_Background_is_color_clear_enabled (VALUE self)
{
    Background* p;
    bool enabled;

    Data_Get_Struct (self, Background, p);
    __TRY__;
    enabled = p->isColorClearEnabled ();
    __CATCH__;
    return enabled ? Qtrue : Qfalse;
}

VALUE ruby_Background_is_depth_clear_enabled (VALUE self)
{
    Background* p;
    Data_Get_Struct (self, Background, p);
    bool enabled;
    __TRY__;
    enabled = p->isDepthClearEnabled ();
    __CATCH__;
    return enabled ? Qtrue : Qfalse;
}

VALUE ruby_Background_set_color (VALUE self, VALUE val_argb)
{
    Background* p;
    Data_Get_Struct (self, Background, p);
    int argb = NUM2INT(val_argb);
    __TRY__;
    p->setColor (argb);
    __CATCH__;
    return Qnil;
}

VALUE ruby_Background_set_color_clear_enable (VALUE self, VALUE val_enable)
{
    Background* p;
    Data_Get_Struct (self, Background, p);
    bool enable = (val_enable == Qtrue) ? true : false;
    __TRY__;
    p->setColorClearEnable (enable);
    __CATCH__;
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
    float x      = NUM2DBL (val_x);
    float y      = NUM2DBL (val_y);
    float width  = NUM2DBL (val_width);
    float height = NUM2DBL (val_height);
    __TRY__;
    p->setCrop (x, y, width, height);
    __CATCH__;
    return Qnil;
}

VALUE ruby_Background_set_depth_clear_enable (VALUE self, VALUE val_enable)
{
    Background* p;
    Data_Get_Struct (self, Background, p);
    bool enable = (val_enable == Qtrue) ? true : false;
    __TRY__;
    p->setDepthClearEnable (enable);
    __CATCH__;
    return Qnil;
}

VALUE ruby_Background_set_image (VALUE self, VALUE val_image)
{
    Background* p;
    Data_Get_Struct (self, Background, p);
    Image2D* img;
    Data_Get_Struct (val_image, Image2D, img);
    __TRY__;
    p->setImage (img);
    __CATCH__;
    return Qnil;
}

VALUE ruby_Background_set_image_mode (VALUE self, VALUE val_mode)
{
    VALUE val_x = rb_ary_entry(val_mode, 0);
    VALUE val_y = rb_ary_entry(val_mode, 1);
    Background* p;
    Data_Get_Struct (self, Background, p);
    float x = NUM2DBL(val_x);
    float y = NUM2DBL(val_y);
    __TRY__;
    p->setImageMode (x, y);
    __CATCH__;
    return Qnil;
}


/**
 * Background::ImageModeAccessor
 */

VALUE ruby_Background_ImageModeAccessor_get_x (VALUE self)
{
    ImageModeAccessor* p;
    Data_Get_Struct (self, ImageModeAccessor, p);
    float x;
    __TRY__;
    x = p->background->getImageModeX ();
    __CATCH__;
    return INT2NUM(x);
}

VALUE ruby_Background_ImageModeAccessor_get_y (VALUE self)
{
    ImageModeAccessor* p;
    Data_Get_Struct (self, ImageModeAccessor, p);
    float y;
    __TRY__;
    y = p->background->getImageModeY ();
    __CATCH__;
    return INT2NUM(y);
}


/**
 * Background::Crop
 */

VALUE ruby_Background_CropAccessor_get_x (VALUE self)
{
    CropAccessor* p;
    Data_Get_Struct (self, CropAccessor, p);
    float x;
    __TRY__;
    x = p->background->getCropX();
    __CATCH__;
    return INT2NUM(x);
}

VALUE ruby_Background_CropAccessor_get_y (VALUE self)
{
    CropAccessor* p;
    Data_Get_Struct (self, CropAccessor, p);
    float y;
    __TRY__;
    y = p->background->getCropY();
    __CATCH__;
    return INT2NUM(y);
}

VALUE ruby_Background_CropAccessor_get_width (VALUE self)
{
    CropAccessor* p;
    Data_Get_Struct (self, CropAccessor, p);
    float width;
    __TRY__;
    width = p->background->getCropWidth();
    __CATCH__;
    return INT2NUM(width);
}

VALUE ruby_Background_CropAccessor_get_height (VALUE self)
{
    CropAccessor* p;
    Data_Get_Struct (self, CropAccessor, p);
    float height;
    __TRY__;
    height = p->background->getCropHeight();
    __CATCH__;
    return INT2NUM(height);
}


void register_Background ()
{
    // Background
    rb_cBackground          = rb_define_class_under (rb_mM3G, "Background", rb_cObject3D);

    rb_define_const (rb_cBackground, "BORDER", INT2NUM(Background::BORDER)); 
    rb_define_const (rb_cBackground, "REPEAT", INT2NUM(Background::REPEAT)); 

    rb_define_alloc_func (rb_cBackground, ruby_Background_allocate);
    rb_define_private_method (rb_cBackground, "initialize", (VALUE(*)(...))ruby_Background_initialize,               0);

    rb_define_method (rb_cBackground, "color",               (VALUE(*)(...))ruby_Background_get_color,               0);
    rb_define_method (rb_cBackground, "crop",                (VALUE(*)(...))ruby_Background_get_crop,                0);
    rb_define_method (rb_cBackground, "image",               (VALUE(*)(...))ruby_Background_get_image,               0);
    rb_define_method (rb_cBackground, "image_mode",          (VALUE(*)(...))ruby_Background_get_image_mode,          0);
    rb_define_method (rb_cBackground, "color_clear_enabled?", (VALUE(*)(...))ruby_Background_is_color_clear_enabled, 0);
    rb_define_method (rb_cBackground, "depth_clear_enabled?", (VALUE(*)(...))ruby_Background_is_depth_clear_enabled, 0);
    rb_define_method (rb_cBackground, "color=",               (VALUE(*)(...))ruby_Background_set_color,              1);
    rb_define_method (rb_cBackground, "color_clear_enable=",  (VALUE(*)(...))ruby_Background_set_color_clear_enable, 1);
    rb_define_method (rb_cBackground, "crop=",                (VALUE(*)(...))ruby_Background_set_crop,               1);
    rb_define_method (rb_cBackground, "depth_clear_enable=",  (VALUE(*)(...))ruby_Background_set_depth_clear_enable, 1);
    rb_define_method (rb_cBackground, "image=",               (VALUE(*)(...))ruby_Background_set_image,              1);
    rb_define_method (rb_cBackground, "image_mode=",          (VALUE(*)(...))ruby_Background_set_image_mode,         1);

    // Background:: ImageModeAccessor
    rb_cBackground_ImageModeAccessor  = rb_define_class_under (rb_cBackground, "ImageModeAccessor", rb_cObject);

    rb_define_method (rb_cBackground_ImageModeAccessor, "x",               (VALUE(*)(...))ruby_Background_ImageModeAccessor_get_x, 0); 
    rb_define_method (rb_cBackground_ImageModeAccessor, "y",               (VALUE(*)(...))ruby_Background_ImageModeAccessor_get_y, 0); 


    // Background:: CropAccessor
    rb_cBackground_CropAccessor  = rb_define_class_under (rb_cBackground, "CropAccessor", rb_cObject);

    rb_define_method (rb_cBackground_CropAccessor, "x",               (VALUE(*)(...))ruby_Background_CropAccessor_get_x,      0); 
    rb_define_method (rb_cBackground_CropAccessor, "y",               (VALUE(*)(...))ruby_Background_CropAccessor_get_y,      0); 
    rb_define_method (rb_cBackground_CropAccessor, "width",           (VALUE(*)(...))ruby_Background_CropAccessor_get_width,  0); 
    rb_define_method (rb_cBackground_CropAccessor, "height",          (VALUE(*)(...))ruby_Background_CropAccessor_get_height, 0); 


}

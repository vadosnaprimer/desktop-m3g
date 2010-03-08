#include <new>
#include "ruby.h"
#include "Background.hpp"
using namespace m3g;

VALUE ruby_Background_free (Background* ptr)
{
    ptr->~Background ();
    ruby_xfree (ptr);
}

VALUE ruby_Background_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Background));
    return Data_Wrap_Struct (self, NULL, ruby_Background_free, p);
}

VALUE ruby_Background_initialize (VALUE self)
{
    Background* p;
    Data_Get_Struct (self, Background, p);
    new (p) Background;
    return Qnil;
}

VALUE ruby_Background_get_color (VALUE self)
{
    return Qnil;
}

VALUE ruby_Background_get_crop (VALUE self)
{
    // x,y,width,heightを配列で返す
    return Qnil;
}

VALUE ruby_Background_get_image (VALUE self)
{
    return Qnil;
}

VALUE ruby_Background_get_image_mode (VALUE self)
{
    // x,y
    return Qnil;
}

VALUE ruby_Background_is_color_clear_enabled (VALUE self)
{
    return Qnil;
}

VALUE ruby_Background_is_depth_clear_enabled (VALUE self)
{
    return Qnil;
}

VALUE ruby_Background_set_color (VALUE self, VALUE argb)
{
    return Qnil;
}

VALUE ruby_Background_set_color_clear_enable (VALUE self, VALUE enable)
{
    return Qnil;
}

VALUE ruby_Background_set_crop (VALUE self, VALUE val_cropX, VALUE val_cropY, VALUE val_width, VALUE val_height)
{
    return Qnil;
}

VALUE ruby_Background_set_depth_clear_enable (VALUE self, VALUE val_enable)
{
    return Qnil;
}
VALUE ruby_Background_set_image (VALUE self, VALUE val_image)
{
    return Qnil;
}
VALUE ruby_Background_set_image_mode (VALUE self, VALUE val_modeX, VALUE val_modeY)
{
    return Qnil;
}



void register_Background (VALUE rb_cBackground)
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
    rb_define_method (rb_cBackground, "crop=",                (VALUE(*)(...))ruby_Background_set_crop, 4); 
    rb_define_method (rb_cBackground, "depth_clear_enable=",  (VALUE(*)(...))ruby_Background_set_depth_clear_enable, 1); 
    rb_define_method (rb_cBackground, "image=",               (VALUE(*)(...))ruby_Background_set_image, 1); 
    rb_define_method (rb_cBackground, "image_mode=",          (VALUE(*)(...))ruby_Background_set_image_mode, 2); 


}
